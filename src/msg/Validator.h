#ifndef MSG_VALIDATOR_H
#define MSG_VALIDATOR_H
#include <rapidjson/document.h>
#include <rapidjson/error/error.h>

#include <string>

namespace msg {
class Validator {
   public:
    Validator(std::string& sourceMsg) : _sourceMsg(sourceMsg){};
    bool vaildMsg(rapidjson::Document& jsonMsg);
    bool vaildLsMsg(rapidjson::Document& jsonMsg);
    std::string getErrMsg() { return _errMsg; }

   private:
    std::string& _sourceMsg;
    std::string _errMsg;
};
}  // namespace msg.

#endif