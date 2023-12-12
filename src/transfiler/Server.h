#ifndef TRANSFILER_SERVER_H
#define TRANSFILER_SERVER_H

#include <memory>

#include "udp/UdpServer.h"
namespace transfiler {
typedef std::unique_ptr<udp::UdpServer> UdpSerPtr;
class Server {
   public:
    Server(EventLoop* loop, const char* host, uint16_t port);
    void readBack();
    void writeBack();

   private:
    UdpSerPtr _udpPtr;
};
}  // namespace transfiler

#endif