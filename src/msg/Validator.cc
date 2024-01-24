
#include <cstring>

#include "Validator.h"
#include "rapidjson/error/en.h"

using namespace msg;

bool Validator::vaildMsg(rapidjson::Document &json) {
    if (json.HasParseError()) {
        _errMsg += "json解析错误.Error:";
        _errMsg += rapidjson::GetParseError_En(json.GetParseError());
        _errMsg += " at offset ";
        _errMsg += json.GetErrorOffset();
        _errMsg += " near '" + std::string(json.GetString()).substr(json.GetErrorOffset(), 10) + "...'";
        return false;
    }
    if (json.HasMember("command") && !json["command"].IsString()) {
        _errMsg = "参数错误";
        return false;
    }
    return true;
}

bool Validator::vaildLsMsg(rapidjson::Document &json) {
    if (!vaildMsg(json)) {
        return false;
    }
    if (std::strcmp(json["command"].GetString(), "ls") != 0) {
        _errMsg = "命令参数错误";
        return false;
    }
    return true;
}
