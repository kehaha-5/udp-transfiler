#ifndef UDP_UDPCLIENT_H
#define UDP_UDPCLIENT_H
#include <netinet/in.h>
#include <unistd.h>

#include <memory>
#include <string>

#include "EventLoop.h"
namespace udp {
typedef std::shared_ptr<EventLoop> evenPtr;
class UdpClient {
   public:
    UdpClient(evenPtr even, std::string &host, __uint16_t port);
    ~UdpClient() { close(_socketfd); }
    bool sendMsg(std::string &msg);
    std::string rev();
    int getSocketfd() { return _socketfd; }

   private:
    int _socketfd;
    struct sockaddr_in _serveraddr;
};
}  // namespace udp

#endif