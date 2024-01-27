#ifndef TRANSFILER_CLIENT_H
#define TRANSFILER_CLIENT_H

#include <rapidjson/document.h>
#include <sys/types.h>

#include <functional>
#include <memory>
#include <mutex>
#include <set>
#include <thread>

#include "EventLoop.h"
#include "Interaction.h"
#include "udp/UdpClient.h"

namespace transfiler {
typedef std::unique_ptr<udp::UdpClient> udpClientPtr;
typedef std::shared_ptr<EventLoop> evevPtr;
typedef std::function<std::string()> msgCb;
typedef std::set<u_long> ackSet;
class Client {
   public:
    Client(std::string host, __uint16_t port);
    void execCommand(interaction::inputCommand command);
    ~Client() { _ackSet.clear(); }

   private:
    void ls();
    void downfile();
    void handleRead();
    void timerExec(u_long ack, std::string msg);
    void sendto(std::string& msg);
    std::string rev();
    udpClientPtr _client;
    interaction::Interaction _os;
    evevPtr _even;
    ackSet _ackSet;
    std::mutex _ackSetLock;
    std::mutex _sendtoLock;
    std::thread _timerThread;
};
}  // namespace transfiler
#endif