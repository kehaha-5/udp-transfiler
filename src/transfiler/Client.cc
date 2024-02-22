#include <rapidjson/document.h>
#include <sys/types.h>

#include <chrono>
#include <functional>
#include <memory>
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
    _ackSet = std::make_shared<ack::AckSet>(_even->getTimer());
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
                _downloaderPtr = std::make_shared<downfile::Downloader>(
                    downloadInfos, config::ClientConfig::getInstance().getDownloadThreadNum(), _even, _client, _ackSet);
                if (!_downloaderPtr->getfilenameExistInfo().empty()) {
                    auto filenameExist = _downloaderPtr->getfilenameExistInfo();
                    std::stringstream msg;
                    msg << "\nfilename is exist can not be download !!!";
                    for (auto& it : filenameExist) {
                        msg << "\n\t" << it;
                    }
                    msg << "\n";
                    _os.showError(msg.str());
                    if (filenameExist.size() == downloadInfos.size()) {
                        _os.showError("all download filename is exist !!! not file will be download !!!");
                        setMsgIoCb();
                        return;
                    }
                }
                std::thread osThread = std::thread(std::bind([this]() {
                    int num = 0;
                    bool getSpeed = false;
                    while (!_downloaderPtr->hasFinish()) {
                        if (num == 1000) {
                            getSpeed = true;
                            num = 0;
                        } else {
                            getSpeed = false;
                        }
                        _os.showMsg(_downloaderPtr->getDownloadStrDetails(getSpeed));
                        num++;
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
                }));
                osThread.detach();

                _downloaderPtr->start();
                _os.showMsg(_downloaderPtr->getDownloadStatistics());
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

void Client::timerExce(u_long ack, std::vector<msg::Package> msg) {
    // avoid create too many protobuf object
    debug_log("the package will be resend ack is %lu", ack);
    PackageMsg protobufMsg;
    std::string sendMsg;
    for (auto& it : msg) {
        it.serialized(&sendMsg, protobufMsg);
        while (!_client->sendMsg(sendMsg)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        };
        protobufMsg.Clear();
    }
}

void Client::sendto(std::string& msg, msg::proto::MsgType type) {
    debug_log("client send msg ");
    auto ack = _ackSet->getAck();

    auto resMsg = msg::getsubcontractInfo(msg, ack, type);

    std::string sendMsg;
    // avoid create too many protobuf object
    PackageMsg protobufMsg;
    for (auto& it : resMsg) {
        it.serialized(&sendMsg, protobufMsg);
        while (!_client->sendMsg(sendMsg)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        };
        protobufMsg.Clear();
    }
    _ackSet->setCbByAck(ack, std::bind(&Client::timerExce, this, ack, resMsg));
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

void Client::clearUp() {
    if (_downloaderPtr != nullptr) {
        _downloaderPtr->flushAllInterruptionData();
    }
}