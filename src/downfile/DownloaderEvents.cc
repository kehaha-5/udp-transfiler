#include <sys/epoll.h>
#include <sys/types.h>

#include <cassert>
#include <cmath>
#include <functional>
#include <memory>

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

DownloaderEvents::DownloaderEvents(EventPtr even, UdpClientPtr client, WriteMapPtr writeMapPtr, int threadNum)
    : _even(even), _client(client), _writeMapPtr(writeMapPtr) {
    _threadPool = std::make_unique<pool::ThreadPool>(threadNum);
    _threadNum = threadNum;
    _ackSetPtr = std::make_shared<ack::AckSet>();
    _even->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::handlerRecv, this), EPOLLIN | EPOLLET);
}

void DownloaderEvents::start(DownQueue &queue, u_long size) {
    FileDownMsg fileDownMsg;
    _lastStatisticsTime = std::chrono::system_clock::now();
    _totalSzie = size;
    initDownloadDetails(queue.front().name);
    std::string msg;
    while (!queue.empty()) {
        for (int i = 0; i < _threadNum; i++) {
            fileDownMsg.set_name(queue.front().name);
            fileDownMsg.set_startpos(queue.front().startPos);
            sendMsg(fileDownMsg);
            fileDownMsg.Clear();
            queue.pop();
        }
        loop();
    }
}

void DownloaderEvents::sendMsg(FileDownMsg &msg) {
    std::string out;
    assert(msg.SerializeToString(&out));
    auto res = msg::getsubcontractInfo(out, _ackSetPtr->getAck(out), msg::proto::FileDownloadRes);
    std::string sendMsg;
    PackageMsg protobufMsg;
    for (auto &it : res) {
        it.serialized(&sendMsg, protobufMsg);
        _client->sendMsg(sendMsg);
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
        _onceLoop++;
        if (_onceLoop == _threadNum) {
            _onceLoop = 0;
            setRunning(false);
        }
    }));
}

downloadDetails &DownloaderEvents::getDownloadDetail(bool getSpeed) {
    if (_hasDownlaodSzie != 0) {
        _downloadDetails.percentage = std::ceil((_hasDownlaodSzie / _totalSzie) * 10);
    }
    if (getSpeed) {
        _downloadDetails.speed = utils::humanReadable((_hasDownlaodSzie - _lastDownloadSzie));
        _lastDownloadSzie = _hasDownlaodSzie;
    }
    return _downloadDetails;
}

void DownloaderEvents::initDownloadDetails(std::string filename) {
    _downloadDetails.filename = filename;
    _downloadDetails.percentage = 0;
    _downloadDetails.speed = "-/-";
}

void DownloaderEvents::loop() {
    setRunning(true);
    _even->loop();
}
