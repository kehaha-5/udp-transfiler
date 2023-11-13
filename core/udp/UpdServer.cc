#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>

#include "EventLoop.h"
#include "Logging.h"
#include "UpdServer.h"
#include "pool/MemPool.h"
#include "pool/ThreadPool.h"

UdpServer::UdpServer(EventLoop* loop, const char* host, uint16_t port) : _loop(loop) {
    // create socket
    _socketFd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    exit_if(_socketFd == -1, "create socket error");

    struct sockaddr_in servaddr;
    ::bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    int ret = inet_aton(host, &servaddr.sin_addr);
    exit_if(ret == 0, "host format %s ", host);
    servaddr.sin_port = htons(port);

    ret = bind(_socketFd, (const struct sockaddr*)&servaddr, sizeof servaddr);
    exit_if(ret == -1, "bind error");

    info_log("this server is running in %s:%i", host, port);

    _mempool = std::make_unique<pool::MemPool>(MAX_MSG_LENGTH, 10, 20);
    info_log("mempool is created size:%d initNum:%d maxNum:%d", MAX_MSG_LENGTH, 10, 20);

    _threadpool = std::make_unique<pool::ThreadPool>(1);
    info_log("threadpool is created threadNum:%d", 1);

    loop->addIo(_socketFd, std::bind(&UdpServer::handleRead, this), EPOLLIN);
}

void UdpServer::handleRead() {
    _threadpool->sendMsg(std::bind(&UdpServer::dispatcherMsg, this));
    debug_log("send a msg to queue")
}

void UdpServer::dispatcherMsg() {
    pool::MemPtr memPtr = _mempool->getMem();
    struct sockaddr_in clientAddr;
    int clientLen = sizeof(clientAddr);
    int len = recvfrom(_socketFd, memPtr->get(), MAX_MSG_LENGTH, 0, (struct sockaddr*)&clientAddr,
                       (socklen_t*)&clientLen);
    info_log("udp recvfrom data %s", memPtr->get());
    _mempool->clear(memPtr);
}
