#ifndef TRANSFILER_SERVER_H
#define TRANSFILER_SERVER_H

#include <sys/types.h>

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "msg/Buffer.h"
#include "msg/Msg.h"
#include "udp/UdpServer.h"
namespace transfiler {
typedef std::unique_ptr<udp::UdpServer> UdpSerPtr;
typedef std::shared_ptr<msg::Buffer> MsgBuffPtr;
typedef std::unordered_map<u_long, MsgBuffPtr> MsgBuffMap;

class Server {
   public:
    Server(EventLoop* loop, const char* host, uint16_t port);
    ~Server() { _msgBuffMap.clear(); }
    void readBack();
    void writeBack();

   private:
    UdpSerPtr _udpPtr;
    MsgBuffMap _msgBuffMap = {};
    std::mutex _msgBuffMapLock;
};
}  // namespace transfiler

#endif