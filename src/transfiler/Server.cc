#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "Constant.h"
#include "Logging.h"
#include "Server.h"
#include "msg/Buffer.h"
#include "msg/Msg.h"
#include "msg/proto/package_msg.pb.h"
#include "msgHandler/Handler.h"

using namespace transfiler;

Server::Server(EventLoop* loop, const char* host, uint16_t port, u_short threadNum) {
    _udpPtr = std::make_unique<udp::UdpServer>(loop, host, port, threadNum);
    _udpPtr->setReadBack(std::bind(&Server::readBack, this));
}

void Server::readBack() {
    std::string data(MAX_MSG_LENGTH, '\0');
    struct sockaddr_in clientAddr = {};
    int clientLen = sizeof(clientAddr);
    int len = recvfrom(_udpPtr->getSocketfd(), &data[0], MAX_MSG_LENGTH, 0, (struct sockaddr*)&clientAddr, (socklen_t*)&clientLen);
    std::string host(IP_V4_LEN, '\0');
    inet_ntop(AF_INET, &clientAddr.sin_addr, &host[0], sizeof(host));
    auto prot = ntohs(clientAddr.sin_port);
    if (len == 0) {
        warn_log("get data len is 0");
        return;
    }
    if (len == -1) {
        warn_log("len is -1 error is %s", strerror(errno));
        return;
    }
    // make sure parse data success
    data.resize(len);
    msg::Package msg;
    std::string errMsg;
    // build package msg
    if (!msg.build(data, errMsg)) {
        warn_log("build package msg fail err is %s ", errMsg.c_str());
        return;
    }
    // add package msg in buffer to componenting the full msg
    MsgBuffPtr msgBuff = std::make_unique<msg::Buffer>();
    {
        std::lock_guard<std::mutex> lock_guard(_msgBuffMapLock);
        auto it = _msgBuffMap.find(msg.ack);
        if (it != _msgBuffMap.end()) {
            msgBuff = it->second;
        } else {
            _msgBuffMap.insert({msg.ack, msgBuff});
        }
        msgBuff->setData(msg);
    }
    res_log("udp recvfrom data to ip %s prot %d ack is %lu", host.data(), prot, msgBuff->getAck(), msgBuff->getSize());
    // check full msg has be build finish
    if (msgBuff->hasAllData()) {
        std::string res;
        msgHandler::Handler handler;
        std::vector<msg::Package> resqMsg;
        msg::proto::MsgType resMsgType;
        // handler msg amd subcontract
        if (!handler.handlerCommand(msgBuff, &res, resMsgType)) {
            handler.getErrorMsg(&res);
            resqMsg = msg::getsubcontractInfo(res, msgBuff->getAck(), msg::proto::MsgType::Command);
        } else {
            resqMsg = msg::getsubcontractInfo(res, msgBuff->getAck(), resMsgType);
        }
        // send package
        std::string packageMsg;
        // avoid create too many protobuf object
        PackageMsg protobufMsg;
        for (auto& it : resqMsg) {
            it.serialized(&packageMsg, protobufMsg);
            _udpPtr->sendMsg(packageMsg, clientAddr);
            protobufMsg.Clear();
        }
        {
            std::lock_guard<std::mutex> lock_guard(_msgBuffMapLock);
            _msgBuffMap.erase(msgBuff->getAck());
        }
        res_log("udp send data to ip %s prot %d ack is %lu", host.data(), prot, msgBuff->getAck());
    }
};
