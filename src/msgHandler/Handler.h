#ifndef MSG_HANDLER_COMMAND_H
#define MSG_HANDLER_COMMAND_H

#include <netinet/in.h>

#include <string>

#include "transfiler/Server.h"

namespace msgHandler {
class Handler {
   public:
    bool handlerCommand(transfiler::MsgBuffPtr buff, std::string* res, msg::proto::MsgType& msgType);
    void getErrorMsg(std::string* res);

   private:
    void ls(std::string* out);
    std::string _errMsg;
};
}  // namespace msgHandler

#endif