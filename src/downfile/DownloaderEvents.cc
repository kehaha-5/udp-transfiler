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
#include "ack/AckSet.h"
#include "downfile/Downloader.h"
#include "msg/Buffer.h"
#include "msg/Msg.h"
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

void DownloaderEvents::start(DownQueue &queue, u_long size) {
    _totalSzie = size;
    initDownloadDetails(queue.front().name);
    std::string msg;
    auto loopThread = std::thread(std::bind([this]() { _even->loop(); }));
    FileDownMsg fileDownMsg;
    // debug_log("queue size is %i", queue.size());
    while (!queue.empty() && _even->isRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(100));
        fileDownMsg.set_name(queue.front().name);
        fileDownMsg.set_startpos(queue.front().startPos);
        sendMsg(fileDownMsg);
        fileDownMsg.Clear();
        _totalSendPackages++;
        queue.pop();
    }
    loopThread.join();
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
    _ackSetPtr->setCbByAck(ack, std::bind(&DownloaderEvents::timerExce, this, ack, resMsg));
}

void DownloaderEvents::timerExce(u_long ack, std::vector<msg::Package> msg) {
    // avoid create too many protobuf object
    // debug_log("will be resend ack is %lu", ack);
    PackageMsg protobufMsg;
    std::string sendMsg;
    for (auto &it : msg) {
        it.serialized(&sendMsg, protobufMsg);
        _client->sendMsg(sendMsg);
        protobufMsg.Clear();
    }
}

void DownloaderEvents::handlerRecv() {
    _threadPool->sendMsg(std::bind([this]() {
        auto data = _client->rev();
        msg::Buffer msgBuffer;
        msgBuffer.setData(data);
        if (msgBuffer.getMsgType() != msg::proto::FileDownloadRes) {
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

        _hasDownlaodSzie += MAX_FILE_DATA_SIZE;
        _ackSetPtr->delMsgByAck(msgBuffer.getAck());
        _hasRecvPackages++;
        if (_hasDownlaodSzie >= _totalSzie) {
            _even->setRunning(false);
        }
    }));
}

downloadDetails &DownloaderEvents::getDownloadDetail(bool getSpeed) {
    std::lock_guard<std::mutex> lock_guard(_detailsLock);
    _downloadDetails.percentage = std::round(((_hasDownlaodSzie * 10 / _totalSzie)));
    _downloadDetails.hasDownlaodSzie = _hasDownlaodSzie;
    _downloadDetails.totalSize = _totalSzie;
    _downloadDetails.hasRecvPackages = _hasRecvPackages;
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
    _lastDownloadSzie = 1;
    _totalSendPackages = 1;
    _hasRecvPackages = 0;
    _downloadDetails.filename = filename;
    _downloadDetails.percentage = 0;
    _downloadDetails.speed = "-/-";
    _downloadDetails.totalSize = _totalSzie;
    _downloadDetails.hasDownlaodSzie = 0;
    _downloadDetails.hasRecvPackages = 0;
    _downloadDetails.totalSendPackage = 0;
}

void DownloaderEvents::loop() {
    setRunning(true);
    _even->loop();
}
