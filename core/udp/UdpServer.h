#ifndef UDP_UDPSERVER_H
#define UDP_UDPSERVER_H

#include <arpa/inet.h>

#include <functional>

#include "EventLoop.h"
#include "pool/ThreadPool.h"

namespace udp {
typedef std::unique_ptr<pool::ThreadPool> ThreadPoolPtr;
typedef std::function<void()> CallBack;

class UdpServer {
   public:
    UdpServer(EventLoop* loop, const char* host, __uint16_t port);
    ~UdpServer() { close(_socketFd); };
    void setReadBack(CallBack cb) { _rb = cb; };
    void setWriteBack(CallBack cb) { _wb = cb; };
    int getSocketfd() { return _socketFd; }
    void sendMsg(std::string& msg, sockaddr_in clientAddr);

   private:
    void handleRead();
    void handleWrite();
    void msgCallBack();
    EventLoop* _loop;
    ThreadPoolPtr _threadpool;
    int _socketFd;
    CallBack _rb;
    CallBack _wb;
};
}  // namespace udp
#endif