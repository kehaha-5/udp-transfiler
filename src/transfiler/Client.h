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
#include "msg/Buffer.h"
#include "msg/proto/package_msg.pb.h"
#include "udp/UdpClient.h"

namespace transfiler {
typedef std::unique_ptr<udp::UdpClient> udpClientPtr;
typedef std::shared_ptr<EventLoop> evevPtr;
typedef std::function<std::string()> msgCb;
typedef std::set<u_long> ackSet;
typedef std::function<void()> HandlerRecvCb;

class Client {
   public:
    Client(std::string host, __uint16_t port);
    void execCommand(interaction::inputCommand command);
    ~Client() { _ackSet.clear(); }
    std::string rev() { return _client->rev(); }

   private:
    void ls();
    void downfile(std::string& args);
    void handleRead();
    void timerExec(u_long ack, std::string msg);
    void sendto(std::string& msg, msg::proto::MsgType type);
    void listenResq();
    void setHandlerRecvCb(HandlerRecvCb cb) { _handlerRecvCd = cb; }
    void listenResqAndHandler();
    void setMsgIoCb() { _even->addIo(_client->getSocketfd(), std::bind(&Client::listenResq, this), EPOLLIN | EPOLLET); };
    udpClientPtr _client;
    interaction::Interaction _os;
    evevPtr _even;
    ackSet _ackSet;
    std::mutex _ackSetLock;
    std::mutex _sendtoLock;
    std::thread _timerThread;
    msg::Buffer _msgBuffer;
    HandlerRecvCb _handlerRecvCd;
};
}  // namespace transfiler
#endif