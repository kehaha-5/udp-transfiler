#include "Command.h"
#include "file/Directory.h"
#include "msg/Command.h"
using namespace msgHandler;

std::string Command::handler() {
    if (!_jsonMsg["command"].IsString()) {
        return msg::errMsg("参数错误").jsonStr();
    }
    auto workfile = file::Directory::getInstance();
    std::string command = _jsonMsg["command"].GetString();
    if (command == "ls") {
        msg::lsMsg msg;
        msg.files = workfile->ls();
        return msg.jsonStr();
    };

    return msg::errMsg("未知错误").jsonStr();
}
