#include "Handler.h"
#include "file/server/Directory.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/package_msg.pb.h"

using namespace msgHandler;

bool Handler::handlerCommand(transfiler::MsgBuffPtr buff, std::string* res, msg::proto::MsgType& msgType) {
    switch (buff->getMsgType()) {
        case msg::proto::Command:
            ls(res);
            msgType = msg::proto::MsgType::FileInfos;
            return true;
            break;
        case msg::proto::FileInfos:
            return true;
            break;
        default:
            _errMsg = "can not identify msg type";
            return false;
    }
}

void Handler::ls(std::string* out) {
    auto fileInfos = file::server::Directory::getInstance().ls();
    msg::FileInfos fileMsg;
    fileMsg.infos = fileInfos;
    fileMsg.serialized(out);
}

void Handler::getErrorMsg(std::string* res) {
    msg::Command errMsg;
    errMsg.command = msg::proto::COMMAND_ERRORMSG;
    errMsg.msg = _errMsg;
    errMsg.serialized(res);
}
