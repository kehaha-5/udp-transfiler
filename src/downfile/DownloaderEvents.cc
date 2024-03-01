#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>

#include <cassert>
#include <chrono>
#include <cstring>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include "Constant.h"
#include "DownloaderEvents.h"
#include "EventLoop.h"
#include "Logging.h"
#include "downfile/DownloadSpeedsLimiter.h"
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
    _threadPool = std::make_shared<pool::ThreadPool>(threadNum);
    _threadNum = threadNum;
    _recvEvent->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::handlerRecv, this), EPOLLIN);
    std::thread eventThread = std::thread(std::bind(&DownloaderEvents::listenResq, this));
    eventThread.detach();
    _sendEvent = std::make_shared<EventLoop>();
    _downloadSpeedsLimiterPtr = std::make_shared<DownloadSpeedsLimiter>();
}

void DownloaderEvents::start(interruption::DownfileInterruptionInfo* downloadQueue, u_long size) {
    _running = true;
    _currInterruptionData = downloadQueue;
    for (u_long i = 0; i < _currInterruptionData->info_size(); i++) {
        if (!_currInterruptionData->info(i).isdownload()) {
            sendQueueItem sd = {_currInterruptionData->hash(), _currInterruptionData->info(i).posindex()};
            _sendDataQueue.push(sd);
        }
    }
    _sendEvent->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::setDataWithEvents, this), EPOLLOUT | EPOLLET);
    while (!(_downloaderStatisticsPtr->currTaskHasDownloadFinish())) {
        if (!_sendDataQueue.empty() && !_err) {
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
                auto now = std::chrono::system_clock::now();
                std::chrono::milliseconds duration(SEND_THREAD_WAIT_FOR_ACK_SET_MS);
                if (!_ackSetPtr->_ackLimitCv.wait_until(lk, (now + duration), [this]() { return !_ackSetPtr->ackSizeFull(); })) {
                    continue;
                    ;
                }
                _ackSetPtr->_waittingforCv = false;
            }
        }
    }

    auto it = _writeMapPtr->find(downloadQueue->hash());
    if (!it->second->flush()) {
        _downloaderStatisticsPtr->setDownloadError(it->second->getErrorMsg());
    }
    _downloadSpeedsLimiterPtr->Clear();
    _currInterruptionData->set_isfinish(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
}

void DownloaderEvents::setDataWithEvents() {
    if (!_running) {
        return;
    }
    std::string msg;
    FileDownMsg fileDownMsg;
    while (!_sendDataQueue.empty()) {
        _downloadSpeedsLimiterPtr->start();
        while (_downloadSpeedsLimiterPtr->allowSend()) {
            if (!_sendDataQueue.empty()) {
                fileDownMsg.set_hash(_sendDataQueue.front().filehash);
                fileDownMsg.set_startpos(_sendDataQueue.front().index * MAX_FILE_DATA_SIZE);
                fileDownMsg.set_dataindex(_sendDataQueue.front().index);
                if (!sendMsg(fileDownMsg)) {
                    _sendEvent->setRunning(false);
                    _downloadSpeedsLimiterPtr->interruption();
                    return;
                }
                _downloadSpeedsLimiterPtr->hasSend();
                _downloaderStatisticsPtr->fetchTotalSendPackets();
                fileDownMsg.Clear();
                _sendDataQueue.pop();
            } else {
                return;
            }
        }
        _downloadSpeedsLimiterPtr->waiting();
    }
    _sendEvent->setRunning(false);
}

bool DownloaderEvents::sendMsg(FileDownMsg& msg) {
    if (_ackSetPtr->ackSizeFull()) {
        return false;
    }
    std::string out;
    if (!msg.SerializeToString(&out)) {
        warn_log("sendMsg SerializeToString error");
        return false;
    }
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
    if (!_running) {
        return;
    }
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
                setErrMsg("download server error " + commandMsg.msg);
            }
            warn_log("recv data error!!! ");
            return;
        }

        FileDownMsg msg;
        msg.ParseFromString(msgBuffer.getData());
        if (!msg.IsInitialized()) {
            debug_log("data Initialized debug str %s", msg.DebugString().c_str());
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

        if (data.empty()) {  // some context mabe empty
            warn_log("data is empty");
            return;
        }

        auto file = _writeMapPtr->find(msg.hash());
        if (!file->second->write(msg.startpos(), msg.data(), msg.size())) {
            warn_log("the file can not be write %s", file->second->getErrorMsg().c_str());
            return;
        }
        _downloaderStatisticsPtr->fetchHasRecvPackets();
        if (!_ackSetPtr->delMsgByAck(msgBuffer.getAck())) {  //数据已经处理过了
            return;
        }
        _downloaderStatisticsPtr->fetchDownloadSize(msg.size());
        {
            std::lock_guard<std::mutex> lock_guard(_updateInterruptionDataLock);
            _currInterruptionData->set_hasdownloadedsize(_currInterruptionData->hasdownloadedsize() + msg.size());
            if (std::strcmp(msg.hash().c_str(), _currInterruptionData->hash().c_str()) == 0) {
                auto data = _currInterruptionData->mutable_info(msg.dataindex());
                data->set_isdownload(true);
            }
        }
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

void DownloaderEvents::stop() {
    _running = false;
    _sendEvent->setRunning(false);
    _recvEvent->setRunning(false);
    _recvEvent->delIo(_client->getSocketfd());
    _threadPool->closeThreadPool(true);
}
