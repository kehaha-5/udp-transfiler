#ifndef UPD_SERVER_H
#define UPD_SERVER_H

#include <unistd.h>

#include <memory>
#include <string>
class EventLoop;

class UdpServer {
   public:
    UdpServer(EventLoop* loop, const char* host, __uint16_t port);
    ~UdpServer() { close(_socketFd); }
    void handleRead();

   private:
    EventLoop* _loop;
    int _socketFd;
};
#endif