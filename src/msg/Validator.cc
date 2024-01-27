

#include "Validator.h"
#include "rapidjson/error/en.h"

using namespace msg;

bool Validator::vaildMsg(rapidjson::Document& _jsonMsg) {
    if (_jsonMsg.HasParseError()) {
        _errMsg += "_jsonMsg解析错误.Error:";
        _errMsg += rapidjson::GetParseError_En(_jsonMsg.GetParseError());
        _errMsg += " at offset ";
        _errMsg += _jsonMsg.GetErrorOffset();
        _errMsg += " near '" + _sourceMsg.substr(_jsonMsg.GetErrorOffset(), 10) + "...'";
        return false;
    }
    if (_jsonMsg.HasMember("command") && !_jsonMsg["command"].IsString()) {
        _errMsg = "参数错误";
        return false;
    }
    return true;
}

bool Validator::vaildLsMsg(rapidjson::Document& _jsonMsg) {
    if (!vaildMsg(_jsonMsg)) {
        return false;
    }
    if (std::strcmp(_jsonMsg["command"].GetString(), "ls") != 0) {
        _errMsg = "命令参数错误";
        return false;
    }
    return true;
}
