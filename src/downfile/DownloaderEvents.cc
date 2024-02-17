#include <sys/epoll.h>
#include <sys/types.h>

#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

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
    std::thread eventThread = std::thread(std::bind(&DownloaderEvents::listenResq, this));
    eventThread.detach();
}

bool DownloaderEvents::start(DownQueue &queue, u_long size) {
    _totalSzie = size;
    initDownloadDetails(queue.front().name);
    std::string msg;
    FileDownMsg fileDownMsg;
    while (!queue.empty() && _even->isRunning()) {
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < MAX_SEND_PACKETS; i++) {
            if (!queue.empty()) {
                fileDownMsg.set_name(queue.front().name);
                fileDownMsg.set_startpos(queue.front().startPos);
                sendMsg(fileDownMsg);
                fileDownMsg.Clear();
                _totalSendPackets++;
                queue.pop();
            } else {
                break;
            }
        }
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(start - end);
        if (duration.count() < 1000 && !queue.empty()) {  //小于1秒
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 - duration.count()));
        }
        {
            std::lock_guard<std::mutex> lock_guard(_seterrLock);
            if (_err) {
                _downloadDetails.iserr = true;
                _downloadDetails.errMsg = getErrMsg();
                return false;
            }
        }
    }

    while (!(_hasRecvPackets >= _totalSendPackets)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;
}

void DownloaderEvents::sendMsg(FileDownMsg &msg) {
    std::string out;
    assert(msg.SerializeToString(&out));
    auto ack = _ackSetPtr->getAck();
    auto resMsg = msg::getsubcontractInfo(out, ack, msg::proto::FileDownloadRes);
    std::string sendMsg;
    PackageMsg protobufMsg;
    // debug_log("send data ack is %lu", ack);
    _ackSetPtr->setCbByAck(ack, std::bind(&DownloaderEvents::timerExce, this, ack, resMsg));
    for (auto &it : resMsg) {
        it.serialized(&sendMsg, protobufMsg);
        _client->sendMsg(sendMsg);
    }
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
        _hasResendPackets++;
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

        _hasDownlaodSzie += msg.size();
        _ackSetPtr->delMsgByAck(msgBuffer.getAck());
        _hasRecvPackets++;

    }));
}

downloadDetails &DownloaderEvents::getDownloadDetail(bool getSpeed) {
    std::lock_guard<std::mutex> lock_guard(_detailsLock);
    _downloadDetails.percentage = std::round(((_hasDownlaodSzie * 100 / _totalSzie)));
    _downloadDetails.hasDownlaodSzie = _hasDownlaodSzie;
    _downloadDetails.hasRecvPackets = _hasRecvPackets.load();
    _downloadDetails.totalSendPackets = _totalSendPackets;
    _downloadDetails.hasResendPackets = _hasResendPackets;
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
    _totalSendPackets = 0;
    _hasResendPackets = 0;
    _hasRecvPackets.store(0);
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
