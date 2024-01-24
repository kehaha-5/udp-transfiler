#ifndef UDP_UDPCLIENT_H
#define UDP_UDPCLIENT_H
#include <netinet/in.h>

#include <memory>
#include <string>

#include "EventLoop.h"
namespace udp {
typedef std::shared_ptr<EventLoop> evenPtr;
class UdpClient {
   public:
    UdpClient(evenPtr even, std::string &host, __uint16_t port);
    void sendMsg(std::string &msg);
    const char *rev();

   private:
    int _socketfd;
    struct sockaddr_in _serveraddr;
};
}  // namespace udp

#endif