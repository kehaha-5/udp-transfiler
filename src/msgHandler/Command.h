#ifndef MSG_HANDLER_COMMAND_H
#define MSG_HANDLER_COMMAND_H

#include <netinet/in.h>

#include <memory>
#include <string>

#include "rapidjson/document.h"

namespace msgHandler {
class Command {
   public:
    Command(const char* msg) { _jsonMsg.Parse(msg); };
    ~Command() {
        _jsonMsg.SetNull();
        _jsonMsg.GetAllocator().Clear();
    }
    std::string handler();

   private:
    rapidjson::Document _jsonMsg;
    std::string getCommand();
};
}  // namespace msgHandler

#endif