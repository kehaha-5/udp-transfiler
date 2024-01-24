#include <rapidjson/document.h>
#include <sys/types.h>

#include <memory>
#include <mutex>

#include "Client.h"
#include "EventLoop.h"
#include "Interaction.h"
#include "Logging.h"
#include "msg/Command.h"
#include "msg/Validator.h"
#include "transfiler/AckRandom.h"
#include "udp/UdpClient.h"

using namespace transfiler;

Client::Client(std::string host, __uint16_t port) {
    _even = std::make_unique<EventLoop>();
    _client = std::make_unique<udp::UdpClient>(_even, host, port);
    _even->startTimer();
    _even->setIntervalTimer(0, 100);
    _os = interaction::Interaction();
}

void Client::execCommand(interaction::inputCommand command) {
    if (command.command == "ls") {
        ls();
    }
}

void Client::ls() {
    msg::lsMsg msg = {};
    auto ack = AckRandom::getAck();
    msg.ack = ack;
    auto strMsg = msg.jsonStr();
    debug_log("client send msg %s", strMsg.c_str());
    sendto(strMsg);
    {
        std::lock_guard<std::mutex> lock(_ackSetLock);
        _ackSet.insert(ack);
    }

    const char* data = rev();
    if (data == nullptr) {
        _os.showError("服务器或网络异常，接受数据为空，请重试");
    }

    debug_log("rev data is %s", data);
    auto json = rapidjson::Document();
    auto valid = msg::Validator();
    json.Parse(data);
    valid.vaildLsMsg(json);

    msg::lsMsg respMsg = msg::lsMsg::getStruct(json);
    _os.ls(respMsg);
    delete[] data;
}

void Client::timerExec(u_long ack, std::string msg) {
    ackSet::iterator it;
    {
        std::lock_guard<std::mutex> lock(_ackSetLock);
        it = _ackSet.find(ack);
    }
    if (it != _ackSet.end()) {
        debug_log("the package will be resend ack is %s", ack);
        sendto(msg);
    }
}

void Client::sendto(std::string& msg) {
    std::lock_guard<std::mutex> lock(_ackSetLock);
    _client->sendMsg(msg);
}

const char* Client::rev() { return _client->rev(); }
