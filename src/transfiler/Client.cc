#include <rapidjson/document.h>
#include <sys/types.h>

#include <functional>
#include <memory>
#include <mutex>
#include <sstream>

#include "Client.h"
#include "EventLoop.h"
#include "Interaction.h"
#include "Logging.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/package_msg.pb.h"
#include "transfiler/AckRandom.h"
#include "udp/UdpClient.h"

using namespace transfiler;

Client::Client(std::string host, __uint16_t port) {
    _even = std::make_unique<EventLoop>();
    _client = std::make_unique<udp::UdpClient>(_even, host, port);
    _even->startTimer();
    _even->addIo(_client->getSocketfd(), std::bind(&Client::listenResq, this), EPOLLIN | EPOLLET);
    _os = interaction::Interaction();
}

void Client::execCommand(interaction::inputCommand command) {
    switch (command.command) {
        case interaction::LS:
            ls();
            break;
        case interaction::DOWNLOADFILE:
            downfile(command.args);
            break;
        default:
            break;
    };
}

void Client::downfile(std::string& args) {
    msg::Command msg;
    msg.command = msg::proto::COMMAND_DOWNFILE;
    msg.args = args;
    std::string strMsg;
    msg.serialized(&strMsg);
    sendto(strMsg, msg::proto::MsgType::Command);
    setHandlerRecvCb(std::bind([this]() {
        msg::FileDownInfo msg;
        std::string errMsg;

        if (_msgBuffer.getMsgType() == msg::proto::Command) {
            msg::Command msg;
            if (msg.build(_msgBuffer.getData(), errMsg)) {
                errMsg = msg.msg;
            }
            _os.showError(errMsg);
            return;
        }

        if (msg.build(_msgBuffer.getData(), errMsg)) {
            std::stringstream confirmMsg;
            confirmMsg << "do you want to down \n";
            int num = 1;
            for (auto& it : msg.infos) {
                confirmMsg << "\t"
                           << "#" << num << "  " << it.name << "  size:" << it.humanReadableSize << "\n ";
                num++;
            }
            if (_os.confirm(confirmMsg.str())) {
                debug_log("will be down file !!!");
            }
            return;
        }
        _os.showError(errMsg);
    }));
    listenResqAndHandler();
}

void Client::ls() {
    msg::Command msg;
    msg.command = msg::proto::COMMAND_LS;
    std::string strMsg;
    msg.serialized(&strMsg);
    sendto(strMsg, msg::proto::MsgType::Command);
    setHandlerRecvCb(std::bind([this]() {
        msg::FileInfos fileinfos;
        std::string errMsg;
        if (fileinfos.build(_msgBuffer.getData(), errMsg)) {
            _os.ls(fileinfos.infos);
            return;
        }
        _os.showError(errMsg);
    }));

    listenResqAndHandler();
}

void Client::timerExec(u_long ack, std::string msg) {
    ackSet::iterator it;
    {
        std::lock_guard<std::mutex> lock(_ackSetLock);
        it = _ackSet.find(ack);
    }
    if (it != _ackSet.end()) {
        debug_log("the package will be resend ack is %s", ack);
    }
}

void Client::sendto(std::string& msg, msg::proto::MsgType type) {
    debug_log("client send msg ");
    auto ack = AckRandom::getAck();
    {
        std::lock_guard<std::mutex> lock(_ackSetLock);
        _ackSet.insert(ack);
    }

    auto resMsg = msg::getsubcontractInfo(msg, ack, type);

    {
        std::lock_guard<std::mutex> lock(_ackSetLock);
        std::string msg;
        for (auto& it : resMsg) {
            it.serialized(&msg);
            _client->sendMsg(msg);
        }
    }
}

void Client::listenResqAndHandler() {
    _even->setRunning(true);
    _even->loop();
}

void Client::listenResq() {
    auto data = rev();
    if (data.empty()) {
        warn_log("recv data is empty()");
        return;
    }
    msg::Package msg;
    std::string errMsg;
    if (!msg.build(data, errMsg)) {
        warn_log("package msg build fault %s", errMsg.c_str());
    }
    _msgBuffer.setData(msg);

    if (_msgBuffer.hasAllData()) {
        {
            std::lock_guard<std::mutex> lock(_ackSetLock);
            _ackSet.erase(_msgBuffer.getAck());
        }
        _handlerRecvCd();
        _msgBuffer.clear();
        _even->setRunning(false);
        return;
    }
    debug_log("msg not component finsih !!");
}
