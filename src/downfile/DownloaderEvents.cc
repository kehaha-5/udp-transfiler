#include <cassert>
#include <functional>
#include <memory>

#include "DownloaderEvents.h"
#include "ack/AckSet.h"
#include "msg/Msg.h"
#include "msg/proto/file_down_msg.pb.h"
#include "msg/proto/package_msg.pb.h"

using namespace downfile;

DownloaderEvents::DownloaderEvents(EventPtr even, UdpClientPtr client, WriteMapPtr writeMapPtr, int threadNum)
    : _even(even), _client(client), _writeMapPtr(writeMapPtr) {
    _threadPool = std::make_unique<pool::ThreadPool>(threadNum);
    _threadNum = threadNum;
    _ackSetPtr = std::make_shared<ack::AckSet>();
    _even->addIo(_client->getSocketfd(), std::bind(&DownloaderEvents::handlerRecv, this), EPOLLIN | EPOLLET);
}

void DownloaderEvents::start(DownQueue &queue) {
    FileDownMsg fileDownMsg;
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
        file->second->wirite(msg.startpos(), msg.data(), msg.size());
        _onceLoop++;
        if (_onceLoop == _threadNum) {
            _onceLoop = 0;
            setRunning(false);
        }
    }));
}

void DownloaderEvents::loop() {
    setRunning(true);
    _even->loop();
}
