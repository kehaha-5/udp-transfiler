#ifndef MSG_HANDLER_COMMAND_H
#define MSG_HANDLER_COMMAND_H

#include <netinet/in.h>

#include <memory>
#include <string>

#include "msg/Validator.h"
#include "rapidjson/document.h"

typedef std::unique_ptr<msg::Validator> validPtr;

namespace msgHandler {
class Command {
   public:
    Command(std::string& msg) : _valid() {
        _jsonMsg.Parse(msg.c_str());
        _valid = std::make_unique<msg::Validator>(msg);
    };
    std::string handler();

   private:
    bool vaildData();
    std::string getErrorMsg();
    std::string getCommand();
    rapidjson::Document _jsonMsg;
    std::string _errMsg;
    validPtr _valid;
};
}  // namespace msgHandler

#endif