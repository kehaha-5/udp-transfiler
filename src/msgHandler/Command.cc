
#include "Command.h"
#include "file/server/Directory.h"
#include "msg/Msg.h"
using namespace msgHandler;

std::string Command::handler() {
    if (!_valid->vaildMsg(_jsonMsg)) {
        _errMsg = _valid->getErrMsg();
        return getErrorMsg();
    }
    std::string command = _jsonMsg["command"].GetString();
    if (std::strcmp(command.c_str(), "ls") == 0) {
        msg::lsMsg msg;
        msg.files = file::server::Directory::getInstance().ls();
        return msg.jsonStr();
    };
    _errMsg = "未知错误";
    return getErrorMsg();
}

std::string Command::getErrorMsg() {
    auto err = msg::errMsg(_errMsg);
    if (_jsonMsg.HasParseError()) {
        return err.jsonStr();
    }
    return err.jsonStr();
}