#ifndef MSG_HANDLER_COMMAND_H
#define MSG_HANDLER_COMMAND_H

#include <netinet/in.h>

#include <string>

#include "msg/Validator.h"
#include "rapidjson/document.h"

namespace msgHandler {
class Command {
   public:
    Command(const char* msg) {
        _jsonMsg.Parse(msg);
        _valid = msg::Validator();
    };
    std::string handler();

   private:
    bool vaildData();
    std::string getErrorMsg();
    std::string getCommand();
    rapidjson::Document _jsonMsg;
    std::string _errMsg;
    msg::Validator _valid;
};
}  // namespace msgHandler

#endif