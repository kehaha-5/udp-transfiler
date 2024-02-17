#include <sys/epoll.h>
#include <sys/types.h>

#include <cassert>
#include <cmath>
#include <functional>
#include <memory>
#include <mutex>

#include "Constant.h"
#include "DownloaderEvents.h"
#include "Logging.h"
#include "downfile/Downloader.h"
#include "msg/Buffer.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/file_down_msg.pb.h"
#include "msg/proto/package_msg.pb.h"
#include "utils.h"

using namespace downfile;

DownloaderEvents::DownloaderEvents(EventPtr even, UdpClientPtr client, WriteMapPtr writeMapPtr, int threadNum, AckSetPtr ackSetPtr)
    : _even(even), _client(client), _writeMapPtr(writeMapPtr), _ackSetPtr(ackSetPtr) {
    _threadPool = std::make_unique<pool::ThreadPool>(threadNum);
    _threadNum = threadNum;
    _even->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::handlerRecv, this), EPOLLIN);
}

bool DownloaderEvents::start(DownQueue &queue, u_long size) {
    _totalSzie = size;
    initDownloadDetails(queue.front().name);
    std::string msg;
    FileDownMsg fileDownMsg;

    while (!queue.empty()) {
        for (int i = 0; i < 5; i++) {
            if (!queue.empty()) {
                fileDownMsg.set_name(queue.front().name);
                fileDownMsg.set_startpos(queue.front().startPos);
                sendMsg(fileDownMsg);
                fileDownMsg.Clear();
                _totalSendPackages++;
                queue.pop();
            } else {
                break;
            }
        }
        listenResq();
        {
            std::lock_guard<std::mutex> lock_guard(_seterrLock);
            if (_err) {
                _downloadDetails.iserr = true;
                _downloadDetails.errMsg = getErrMsg();
                return false;
            }
        }
    }

    _even->setRunning(false);
    return true;
}

void DownloaderEvents::sendMsg(FileDownMsg &msg) {
    std::string out;
    assert(msg.SerializeToString(&out));
    auto ack = _ackSetPtr->getAck();
    auto resMsg = msg::getsubcontractInfo(out, ack, msg::proto::FileDownloadRes);
    std::string sendMsg;
    PackageMsg protobufMsg;
    for (auto &it : resMsg) {
        it.serialized(&sendMsg, protobufMsg);
        _client->sendMsg(sendMsg);
    }
    // debug_log("send data ack is %lu", ack);
    _ackSetPtr->setCbByAck(ack, std::bind(&DownloaderEvents::timerExce, this, ack, resMsg));
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
    }));
}

void DownloaderEvents::handlerRecv() {
    _threadPool->sendMsg(std::bind([this]() {
        auto data = _client->rev();
        if(data.empty()){
            // warn_log("recv data is emtpy");
            return ;
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

        _hasDownlaodSzie += msgBuffer.getSize();
        _ackSetPtr->delMsgByAck(msgBuffer.getAck());
        _hasRecvPackages++;

        if (_hasRecvPackages >= _totalSendPackages) {
            // debug_log("eventLoop will be set false and _hasRecvPackages is %lu , _totalSendPackages is %lu", _hasRecvPackages.load(),
            //   _totalSendPackages);
            _even->setRunning(false);
        }
    }));
}

downloadDetails &DownloaderEvents::getDownloadDetail(bool getSpeed) {
    std::lock_guard<std::mutex> lock_guard(_detailsLock);
    _downloadDetails.percentage = std::round(((_hasDownlaodSzie * 100 / _totalSzie)));
    _downloadDetails.hasDownlaodSzie = _hasDownlaodSzie;
    _downloadDetails.hasRecvPackages = _hasRecvPackages.load();
    _downloadDetails.totalSendPackage = _totalSendPackages;
    if (getSpeed) {
        _downloadDetails.speed = utils::humanReadable((_hasDownlaodSzie - _lastDownloadSzie));
        _lastDownloadSzie = _hasDownlaodSzie;
    }
    return _downloadDetails;
}

void DownloaderEvents::initDownloadDetails(std::string filename) {
    std::lock_guard<std::mutex> lock_guard(_detailsLock);
    _hasDownlaodSzie = 1;
    _lastDownloadSzie = 0;
    _totalSendPackages = 0;
    _hasRecvPackages.store(0);
    _downloadDetails.clear();
    _downloadDetails.filename = filename;
    _downloadDetails.totalSize = _totalSzie;
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
    _even->setRunning(true);
    _even->loop();
}
