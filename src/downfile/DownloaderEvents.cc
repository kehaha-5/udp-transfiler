#include <sys/epoll.h>
#include <sys/types.h>

#include <cassert>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include "Constant.h"
#include "DownloaderEvents.h"
#include "EventLoop.h"
#include "Logging.h"
#include "downfile/Downloader.h"
#include "msg/Buffer.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/file_down_msg.pb.h"
#include "msg/proto/package_msg.pb.h"

using namespace downfile;

DownloaderEvents::DownloaderEvents(EventPtr& even, UdpClientPtr& client, WriteMapPtr& writeMapPtr, int threadNum, AckSetPtr& ackSetPtr,
                                   DownloaderStatisticsPtr& dfstatisticsPtr)
    : _recvEvent(even), _client(client), _writeMapPtr(writeMapPtr), _ackSetPtr(ackSetPtr), _downloaderStatisticsPtr(dfstatisticsPtr) {
    _threadPool = std::make_unique<pool::ThreadPool>(threadNum);
    _threadNum = threadNum;
    _recvEvent->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::handlerRecv, this), EPOLLIN);
    std::thread eventThread = std::thread(std::bind(&DownloaderEvents::listenResq, this));
    eventThread.detach();
    _sendEvent = std::make_shared<EventLoop>();
}

void DownloaderEvents::start(interruption::DownfileInterruptionInfo* downloadQueue, u_long size) {
    _currInterruptionData = downloadQueue;
    for (u_long i = 0; i < _currInterruptionData->info_size(); i++) {
        if (!_currInterruptionData->info(i).isdownload()) {
            sendQueueItem sd = {_currInterruptionData->name(), _currInterruptionData->info(i).startpos(), i};
            _sendDataQueue.push(sd);
        }
    }
    _sendEvent->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::setDataWithEvents, this), EPOLLOUT | EPOLLET);
    while (!(_downloaderStatisticsPtr->currTaskHasDownloadFinish())) {
        if (!_sendDataQueue.empty()) {
            sendRes();
        }
        {
            std::lock_guard<std::mutex> lock_guard(_seterrLock);
            if (_err) {
                _downloaderStatisticsPtr->setDownloadError(getErrMsg());
                return;
            }
        }
        if (_ackSetPtr->ackSizeFull()) {
            {
                std::unique_lock lk(_ackSetPtr->_limitCvLock);
                _ackSetPtr->_waittingforCv = true;
                _ackSetPtr->_ackLimitCv.wait(lk, [this]() { return !_ackSetPtr->ackSizeFull(); });
                _ackSetPtr->_waittingforCv = false;
            }
        }
    }

    auto it = _writeMapPtr->find(downloadQueue->name());
    if (!it->second->flush()) {
        _downloaderStatisticsPtr->setDownloadError(it->second->getErrorMsg());
    }
    _currInterruptionData->set_isfinish(true);
}

void DownloaderEvents::setDataWithEvents() {
    std::string msg;
    FileDownMsg fileDownMsg;
    u_long index = 0;
    while (!_sendDataQueue.empty()) {
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < MAX_SEND_PACKETS; i++) {
            if (!_sendDataQueue.empty()) {
                fileDownMsg.set_name(_sendDataQueue.front().filename);
                fileDownMsg.set_startpos(_sendDataQueue.front().startPos);
                fileDownMsg.set_dataindex(_sendDataQueue.front().index);
                if (!sendMsg(fileDownMsg)) {
                    _sendEvent->setRunning(false);
                    return;
                } else {
                    _downloaderStatisticsPtr->fetchTotalSendPackets();
                }
                fileDownMsg.Clear();
                _sendDataQueue.pop();
            } else {
                return;
            }
        }
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if ((duration.count() < 1000)) {  //小于1秒
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 - duration.count()));
        }
    }
    _sendEvent->setRunning(false);
}

bool DownloaderEvents::sendMsg(FileDownMsg& msg) {
    if (_ackSetPtr->ackSizeFull()) {
        return false;
    }
    std::string out;
    assert(msg.SerializeToString(&out));
    auto ack = _ackSetPtr->getAck();
    auto resMsg = msg::getsubcontractInfo(out, ack, msg::proto::FileDownloadRes);
    std::string sendMsg;
    PackageMsg protobufMsg;
    // debug_log("send data ack is %lu", ack);
    _ackSetPtr->setCbByAck(ack, std::bind(&DownloaderEvents::timerExce, this, ack, resMsg));
    assert(resMsg.size() == 1);
    resMsg[0].serialized(&sendMsg, protobufMsg);

    return _client->sendMsg(sendMsg);
}

void DownloaderEvents::timerExce(u_long ack, std::vector<msg::Package> msg) {
    // avoid create too many protobuf object
    _threadPool->sendMsg(std::bind([this, ack, msg]() {
        // debug_log("will be resend ack is %lu", ack);
        PackageMsg protobufMsg;
        std::string sendMsg;
        for (auto it : msg) {
            it.serialized(&sendMsg, protobufMsg);
            _client->sendMsg(sendMsg);
            protobufMsg.Clear();
        }
        _downloaderStatisticsPtr->fetchHasResendPackets();
    }));
}

void DownloaderEvents::handlerRecv() {
    _threadPool->sendMsg(std::bind([this]() {
        auto data = _client->rev();
        if (data.empty()) {
            // warn_log("recv data is emtpy");
            return;
        }
        msg::Buffer msgBuffer;
        msgBuffer.setData(data);

        // debug_log("recv data ack is %lu", msgBuffer.getAck());

        if (msgBuffer.getMsgType() != msg::proto::FileDownloadRes) {
            if (msgBuffer.getMsgType() == msg::proto::Command) {
                msg::Command commandMsg;
                std::string errMsg;
                if (!commandMsg.build(msgBuffer.getData(), errMsg)) {
                    setErrMsg("build commandMsg error " + errMsg);
                }
                if (commandMsg.command != msg::proto::COMMAND_ERRORMSG) {
                    setErrMsg("commadMsg error type not COMMAND_ERRORMSG !!! ");
                }
                setErrMsg("download error " + commandMsg.msg);
            }
            warn_log("recv data error!!! ");
            return;
        }

        if (data.empty()) {
            warn_log("recv data is empty()");
            return;
        }

        FileDownMsg msg;
        msg.ParseFromString(msgBuffer.getData());
        if (!msg.IsInitialized()) {
            warn_log("data Initialized error %s", msg.InitializationErrorString().c_str());
            return;
        }
        if (!msg.has_data()) {
            warn_log("msg without data");
            return;
        }
        if (!msg.has_size()) {
            warn_log("msg without data size");
            return;
        }

        auto file = _writeMapPtr->find(msg.name());
        if (!file->second->write(msg.startpos(), msg.data(), msg.size())) {
            warn_log("the file can not be write !!!");
            return;
        }

        _ackSetPtr->delMsgByAck(msgBuffer.getAck());
        {
            std::lock_guard<std::mutex> lock_guard(_updateInterruptionDataLock);
            _currInterruptionData->set_hasdownloadedsize(_currInterruptionData->hasdownloadedsize() + msg.size());
        }
        auto _currQueueIt = _currInterruptionData->info(msg.dataindex());
        _currQueueIt.set_isdownload(true);
        _downloaderStatisticsPtr->fetchHasRecvPackets();
        _downloaderStatisticsPtr->fetchDownloadSize(msg.size());
    }));
}

void DownloaderEvents::setErrMsg(std::string errMsg) {
    std::lock_guard<std::mutex> lock_guard(_seterrLock);
    if (_err) {
        return;
    }
    _err = true;
    _errMsg = errMsg;
}

void DownloaderEvents::listenResq() {
    _recvEvent->setRunning(true);
    _recvEvent->loop();
}

void DownloaderEvents::sendRes() {
    _sendEvent->setRunning(true);
    _sendEvent->loop();
}
