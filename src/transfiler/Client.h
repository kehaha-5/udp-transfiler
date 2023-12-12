#ifndef TRANSFILER_CLIENT_H
#define TRANSFILER_CLIENT_H

#include <functional>
#include <memory>

#include "EventLoop.h"
#include "Interaction.h"
#include "udp/UdpClient.h"

namespace transfiler {
typedef std::unique_ptr<udp::UdpClient> udpClientPtr;
typedef std::shared_ptr<EventLoop> evevPtr;
typedef std::function<std::string()> msgCb;
class Client {
   public:
    Client(std::string host, __uint16_t port);
    void execCommand(interaction::inputCommand command, msgCb cb);

   private:
    void ls();
    void downfile();
    void handleRead();
    udpClientPtr _client;
    evevPtr _even;
    msgCb _cb;
};
}  // namespace transfiler
#endif