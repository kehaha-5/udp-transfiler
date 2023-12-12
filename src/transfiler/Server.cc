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
    _udpPtr->setWriteBack(std::bind(&Server::writeBack, this));
}

void Server::readBack() {
    char buff[MAX_MSG_LENGTH];
    struct sockaddr_in clientAddr;
    int clientLen = sizeof(clientAddr);
    int len = recvfrom(_udpPtr->getSocketfd(), &buff, MAX_MSG_LENGTH, 0, (struct sockaddr*)&clientAddr,
                       (socklen_t*)&clientLen);
    std::string host;
    inet_ntop(AF_INET, &clientAddr.sin_addr, host.data(), sizeof(host));
    auto prot = ntohs(clientAddr.sin_port);
    info_log("udp recvfrom data from ip %s prot %d", host.data(), prot);
    msgHandler::Command handler(buff);
    auto res = handler.handler();
    info_log("handler msg");
    _udpPtr->sendMsg(res, clientAddr);
};

void Server::writeBack(){};