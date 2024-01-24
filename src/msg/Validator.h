#ifndef MSG_VALIDATOR_H
#define MSG_VALIDATOR_H
#include <rapidjson/document.h>
#include <rapidjson/error/error.h>

#include <string>

namespace msg {
class Validator {
   public:
    bool vaildMsg(rapidjson::Document& _jsonMsg);
    bool vaildLsMsg(rapidjson::Document& _jsonMsg);
    std::string getErrMsg() { return _errMsg; }

   private:
    std::string getErrMsgByRapidJsonErrCode(rapidjson::ParseErrorCode errCode);
    std::string _errMsg;
};
}  // namespace msg.

#endif