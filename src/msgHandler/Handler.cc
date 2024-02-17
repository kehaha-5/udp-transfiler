#include <filesystem>

#include "Constant.h"
#include "Handler.h"
#include "Interaction.h"
#include "Logging.h"
#include "config/ServerConfig.h"
#include "file/server/Directory.h"
#include "file/server/File.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/file_down_msg.pb.h"
#include "msg/proto/package_msg.pb.h"
#include "utils.h"

using namespace msgHandler;

bool Handler::handlerCommand(transfiler::MsgBuffPtr buff, std::string* res, msg::proto::MsgType& msgType) {
    switch (buff->getMsgType()) {
        case msg::proto::Command: {
            msg::Command commandMsg;
            if (!commandMsg.build(buff->getData(), _errMsg)) {
                return false;
            }
            switch (commandMsg.command) {
                case msg::proto::COMMAND_LS:
                    ls(res, msgType);
                    break;
                case msg::proto::COMMAND_DOWNFILE:
                    return downfile(commandMsg.args, res, msgType);
                    break;
                case msg::proto::COMMAND_ERRORMSG:
                    break;
            }
            return true;
        }
        case msg::proto::FileDownloadRes: {
            msg::proto::FileDownMsg resqMsg;
            if (!msg::basePaserAndValidateMsg<msg::proto::FileDownMsg>(resqMsg, buff->getData(), _errMsg)) {
                return false;
            }
            msgType = msg::proto::FileDownloadRes;
            return downfileRes(resqMsg, res);
        }
        default: {
            _errMsg = "can not identify msg type";
            return false;
        }
    }
}

void Handler::ls(std::string* out, msg::proto::MsgType& msgType) {
    auto fileInfos = file::server::Directory::getInstance().ls();
    msg::FileInfos fileMsg;
    fileMsg.infos = fileInfos;
    fileMsg.serialized(out);
    msgType = msg::proto::MsgType::FileInfos;
}

bool Handler::downfile(std::string& arg, std::string* out, msg::proto::MsgType& msgType) {
    unsigned long pos;
    if ((pos = arg.find(interaction::DWONLOADFILE_FILE_ARG)), pos != std::string::npos) {
        auto fileName = utils::trim(arg.substr(pos + interaction::DWONLOADFILE_FILE_ARG.size()));
        if (fileName.empty()) {
            _errMsg = "file name is empty";
            return false;
        }
        file::server::filesDownInfo data;
        if (file::server::Directory::getInstance().getSpecialFileDownInfo(data, fileName, _errMsg)) {
            msg::FileDownInfo msg = {};
            msg.infos = data;
            msg.serialized(out);
            msgType = msg::proto::MsgType::FileDownloadInfo;
            return true;
        }
        return false;
    }
    if ((pos = arg.find(interaction::DWONLOADFILE_ALL_ARG)), pos != std::string::npos) {
        file::server::filesDownInfo data;
        if (!file::server::Directory::getInstance().getAllFileDownInfo(data, _errMsg)) {
            return false;
        }
        msg::FileDownInfo msg = {};
        msg.infos = data;
        msg.serialized(out);
        msgType = msg::proto::MsgType::FileDownloadInfo;
        return true;
    }
    _errMsg = "unkown args";
    return false;
}

bool Handler::downfileRes(msg::proto::FileDownMsg& resqMsg, std::string* out) {
    auto filePath = config::ServerConfig::getInstance().getFilepath();
    file::server::File file(filePath.append(resqMsg.name()));
    file::server::fileData data = {};
    if (!file.getPosContext(resqMsg.startpos(), MAX_FILE_DATA_SIZE, data)) {
        _errMsg = file.getErrMsg().errMsg;
        warn_log("downfileRes error %s", _errMsg.c_str());
        return false;
    };
    resqMsg.set_data(data.data);
    resqMsg.set_size(data.realSize);
    resqMsg.SerializeToString(out);
    return true;
}

void Handler::getErrorMsg(std::string* res) {
    msg::Command errMsg;
    errMsg.command = msg::proto::COMMAND_ERRORMSG;
    errMsg.msg = _errMsg;
    errMsg.serialized(res);
}
