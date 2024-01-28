#include <netinet/in.h>

#include <functional>
#include <memory>

#include "Constant.h"
#include "Logging.h"
#include "Server.h"
#include "msgHandler/Command.h"

using namespace transfiler;

Server::Server(EventLoop* loop, const char* host, uint16_t port) {
    _udpPtr = std::make_unique<udp::UdpServer>(loop, host, port);
    _udpPtr->setReadBack(std::bind(&Server::readBack, this));
}

void Server::readBack() {
    std::string data(MAX_MSG_LENGTH, '\0');
    struct sockaddr_in clientAddr;
    int clientLen = sizeof(clientAddr);
    int len = recvfrom(_udpPtr->getSocketfd(), &data[0], MAX_MSG_LENGTH, 0, (struct sockaddr*)&clientAddr, (socklen_t*)&clientLen);
    std::string host(IP_V4_LEN, '\0');
    inet_ntop(AF_INET, &clientAddr.sin_addr, &host[0], sizeof(host));
    auto prot = ntohs(clientAddr.sin_port);
    info_log("udp recvfrom data from ip %s prot %d", host.data(), prot);
    if (len == 0) {
        info_log("get data len is 0");
        return;
    }
    info_log("data is %s", data.c_str());
    data.reserve(len);

    msgHandler::Command handler(data);
    auto res = handler.handler();
    info_log("handler msg respones is %s", res.c_str());
    _udpPtr->sendMsg(res, clientAddr);
};
