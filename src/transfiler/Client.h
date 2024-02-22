#ifndef TRANSFILER_CLIENT_H
#define TRANSFILER_CLIENT_H

#include <rapidjson/document.h>
#include <sys/types.h>

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include "EventLoop.h"
#include "Interaction.h"
#include "ack/AckSet.h"
#include "downfile/Downloader.h"
#include "msg/Buffer.h"
#include "msg/Msg.h"
#include "msg/proto/package_msg.pb.h"
#include "udp/UdpClient.h"

namespace transfiler {
typedef std::shared_ptr<EventLoop> evenPtr;
typedef std::function<std::string()> msgCb;
typedef std::shared_ptr<udp::UdpClient> udpClientPtr;
typedef std::function<void()> HandlerRecvCb;
typedef std::shared_ptr<ack::AckSet> AckSetPtr;
typedef std::shared_ptr<downfile::Downloader> DownloaderPtr;

class Client {
   public:
    Client(std::string host, __uint16_t port);
    void execCommand(interaction::inputCommand command);
    void setHandlerRecvCb(HandlerRecvCb cb) { _handlerRecvCd = cb; }
    void clearUp();

   private:
    void ls();
    std::string rev() { return _client->rev(); }
    void sendto(std::string& msg, msg::proto::MsgType type);
    void listenResqAndHandler();
    void handleRead();
    void listenResq();
    void downfile(std::string& args);
    void timerExce(u_long ack, std::vector<msg::Package> msg);
    void setMsgIoCb() { _even->addIo(_client->getSocketfd(), std::bind(&Client::listenResq, this), EPOLLIN); };
    udpClientPtr _client;
    interaction::Interaction _os;
    evenPtr _even;
    AckSetPtr _ackSet;
    std::mutex _sendtoLock;
    std::thread _timerThread;
    HandlerRecvCb _handlerRecvCd;
    msg::Buffer _msgBuffer;
    DownloaderPtr _downloaderPtr;
};
}  // namespace transfiler
#endif