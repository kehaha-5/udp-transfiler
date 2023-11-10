#ifndef UPD_SERVER_H
#define UPD_SERVER_H

#include <unistd.h>

#include <memory>
#include <string>

#include "pool/MemPool.h"
#include "pool/ThreadPool.h"

class EventLoop;
typedef std::unique_ptr<pool::MemPool> MemPoolPtr;
typedef std::unique_ptr<pool::ThreadPool> ThreadPoolPtr;

const int MAX_MSG_LENGTH = 2048;

class UdpServer {
   public:
    UdpServer(EventLoop* loop, const char* host, __uint16_t port);
    ~UdpServer() { close(_socketFd); }
    void handleRead();

   private:
    void dispatcherMsg();
    EventLoop* _loop;
    MemPoolPtr _mempool;
    ThreadPoolPtr _threadpool;
    int _socketFd;
};
#endif