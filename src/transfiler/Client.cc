#include <rapidjson/document.h>
#include <sys/types.h>

#include <functional>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>

#include "Client.h"
#include "EventLoop.h"
#include "Interaction.h"
#include "Logging.h"
#include "ack/AckSet.h"
#include "config/ClientConfig.h"
#include "downfile/Downloader.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/package_msg.pb.h"
#include "udp/UdpClient.h"

using namespace transfiler;

Client::Client(std::string host, __uint16_t port) {
    _even = std::make_shared<EventLoop>();
    _client = std::make_shared<udp::UdpClient>(_even, host, port);
    _even->startTimer();
    _os = interaction::Interaction();
    _ackSet = std::make_unique<ack::AckSet>();
    setMsgIoCb();
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
            std::stringstream notDownloadMsg;
            file::server::filesDownInfo downloadInfos;
            confirmMsg << "do you want to down \n";
            notDownloadMsg << "the file size is 0.00B can not be download !!! \n";
            int num = 1;
            int notDownloadNum = 1;
            for (auto& it : msg.infos) {
                if (it.size > 0) {
                    confirmMsg << "\t"
                               << "#" << num << "  " << it.name << "  size:" << it.humanReadableSize << "\n ";
                    num++;
                    downloadInfos.push_back(std::move(it));
                }
                if (it.size == 0) {
                    notDownloadMsg << "\t"
                                   << "#" << notDownloadNum << "  " << it.name << "  size:" << it.humanReadableSize << "\n ";
                    notDownloadNum++;
                }
            }
            if (notDownloadNum != 0) {
                _os.showError(notDownloadMsg.str());
            }
            if (_os.confirm(confirmMsg.str())) {
                debug_log("will be down file !!!");
                downfile::Downloader downloader(downloadInfos, config::ClientConfig::getInstance().getDownloadThreadNum(), _even, _client);
                std::thread osThread = std::thread(std::bind([&downloader, this]() {
                    int num = 0;
                    bool getSpeed = false;
                    while (!downloader.hasFinish()) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        if (num == 10) {
                            getSpeed = true;
                            num = 0;
                        }
                        _os.showMsg(downloader.getDownloadStrDetails(getSpeed));
                        num++;
                    }
                }));
                osThread.detach();
                downloader.start();
                setMsgIoCb();
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

void Client::timerExec(u_long ack) { auto msg = _ackSet->getMsgByAck(ack); }

void Client::sendto(std::string& msg, msg::proto::MsgType type) {
    debug_log("client send msg ");
    auto ack = _ackSet->getAck(msg);

    auto resMsg = msg::getsubcontractInfo(msg, ack, type);

    {
        std::lock_guard<std::mutex> lock(_sendtoLock);
        std::string msg;
        // avoid create too many protobuf object
        PackageMsg protobufMsg;
        for (auto& it : resMsg) {
            it.serialized(&msg, protobufMsg);
            _client->sendMsg(msg);
            protobufMsg.Clear();
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

    _msgBuffer.setData(data);

    if (_msgBuffer.hasAllData()) {
        _ackSet->delMsgByAck(_msgBuffer.getAck());
        _handlerRecvCd();
        _msgBuffer.clear();
        _even->setRunning(false);
        return;
    }
    debug_log("msg not component finsih !!");
}
