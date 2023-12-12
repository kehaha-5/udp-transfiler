#include <sys/epoll.h>
#include <sys/socket.h>

#include <functional>
#include <memory>

#include "Logging.h"
#include "UdpServer.h"
#include "pool/ThreadPool.h"

using namespace udp;

UdpServer::UdpServer(EventLoop* loop, const char* host, uint16_t port) : _loop(loop) {
    // create socket
    _socketFd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    exit_if(_socketFd == -1, "create socket error");

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    int ret = inet_aton(host, &servaddr.sin_addr);
    exit_if(ret == 0, "host format %s ", host);
    servaddr.sin_port = htons(port);

    ret = bind(_socketFd, (const struct sockaddr*)&servaddr, sizeof servaddr);
    exit_if(ret == -1, "bind error");

    info_log("this server is running in %s:%i", host, port);

    _threadpool = std::make_unique<pool::ThreadPool>(1);
    info_log("threadpool is created threadNum:%d", 1);

    loop->addIo(_socketFd, std::bind(&UdpServer::handleRead, this), EPOLLIN | EPOLLET);
}

void UdpServer::sendMsg(std::string& msg, sockaddr_in clientAddr) {
    int res =
        sendto(_socketFd, msg.c_str(), msg.size(), 0, (const struct sockaddr*)&clientAddr, sizeof clientAddr);
    exit_if(res == -1, "sendMsg");
}

void UdpServer::handleRead() { _threadpool->sendMsg(_rb); }

void UdpServer::handleWrite() { _threadpool->sendMsg(_wb); }