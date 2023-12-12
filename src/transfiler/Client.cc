#include <memory>

#include "Client.h"
#include "EventLoop.h"
#include "Logging.h"
#include "msg/Command.h"
#include "udp/UdpClient.h"

using namespace transfiler;

Client::Client(std::string host, __uint16_t port) {
    _even = std::make_unique<EventLoop>();
    _client = std::make_unique<udp::UdpClient>(_even, host, port);
}

void Client::execCommand(interaction::inputCommand command, msgCb cb) {
    if (command.command == "ls") {
        ls();
        
    }
}

void Client::ls() {
    msg::lsMsg msg = {};
    auto strMsg = msg.jsonStr();
    debug_log("client send msg %s", strMsg.c_str());
    _client->sendMsg(strMsg);

}
