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
    _currDownloadQueue = downloadQueue;
    _sendDataFinish = false;
    _sendEvent->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::setDataWithEvents, this), EPOLLOUT | EPOLLET);
    while (!(_downloaderStatisticsPtr->currTaskHasDownloadFinish()) || !_sendDataFinish) {
        if (!_sendDataFinish) {
            sendRes();
        }
        {
            std::lock_guard<std::mutex> lock_guard(_seterrLock);
            if (_err) {
                _downloaderStatisticsPtr->setDownloadError(getErrMsg());
            }
        }
    }

    auto it = _writeMapPtr->find(downloadQueue->name());
    if (!it->second->flush()) {
        _downloaderStatisticsPtr->setDownloadError(it->second->getErrorMsg());
    }
    _currDownloadQueue->set_isfinish(true);
}

void DownloaderEvents::setDataWithEvents() {
    std::string msg;
    FileDownMsg fileDownMsg;
    uint index = 0;
    for (index = 0; index < _currDownloadQueue->info_size(); index += MAX_SEND_PACKETS) {
        auto start = std::chrono::system_clock::now();
        auto i = 0;
        for (int j = 1; j <= MAX_SEND_PACKETS;) {
            if (index + i < _currDownloadQueue->info_size()) {
                if (!_currDownloadQueue->info(index + i).isdownload()) {
                    fileDownMsg.set_name(_currDownloadQueue->name());
                    fileDownMsg.set_startpos(_currDownloadQueue->info(index + i).startpos());
                    fileDownMsg.set_dataindex(index + i);
                    if (!sendMsg(fileDownMsg)) {
                        _sendEvent->setRunning(false);
                    }
                    fileDownMsg.Clear();
                    _downloaderStatisticsPtr->fetchTotalSendPackets();
                    j++;  //避免已经下载的数据占发送位置
                }
            } else {
                break;
            }
            i++;
        }
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(start - end);
        if ((duration.count() < 1000 && duration.count() > 0) && (index + 1) < _currDownloadQueue->info_size()) {  //小于1秒
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 - duration.count()));
        }
    }
    _sendDataFinish = true;
    _sendEvent->setRunning(false);
}

bool DownloaderEvents::sendMsg(FileDownMsg& msg) {
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
        _downloaderStatisticsPtr->fetchDownloadSize(msg.size());
        _downloaderStatisticsPtr->fetchHasRecvPackets();
        {
            std::lock_guard<std::mutex> lock_guard(_updateInterruptionDataLock);
            _currDownloadQueue->set_hasdownloadedsize(_currDownloadQueue->hasdownloadedsize() + msg.size());
        }
        auto _currQueueIt = _currDownloadQueue->info(msg.dataindex());
        _currQueueIt.set_isdownload(true);
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
