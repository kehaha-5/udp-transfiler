#ifndef UDP_UDPCLIENT_H
#define UDP_UDPCLIENT_H
#include <netinet/in.h>

#include <functional>
#include <memory>
#include <string>

#include "EventLoop.h"
namespace udp {
typedef std::function<void()> CallBack;
typedef std::shared_ptr<EventLoop> evenPtr;
class UdpClient {
   public:
    UdpClient(evenPtr even, std::string &host, __uint16_t port);
    void sendMsg(std::string &msg);
    int getSocketfd() { return _socketfd; }
    void handleRead();
    void setRb(CallBack rb) { _rb = rb; };

   private:
    int _socketfd;
    struct sockaddr_in _serveraddr;
    CallBack _rb;
};
}  // namespace udp

#endif