#ifndef MSG_HANDLER_COMMAND_H
#define MSG_HANDLER_COMMAND_H

#include <netinet/in.h>

#include <string>

#include "msg/proto/file_down_msg.pb.h"
#include "transfiler/Server.h"

namespace msgHandler {
class Handler {
   public:
    bool handlerCommand(transfiler::MsgBuffPtr buff, std::string* res, msg::proto::MsgType& msgType);
    void getErrorMsg(std::string* res);

   private:
    void ls(std::string* out, msg::proto::MsgType& msgType);
    bool downfile(std::string& arg, std::string* out, msg::proto::MsgType& msgType);
    bool downfileRes(msg::proto::FileDownMsg& resqMsg, std::string* out);
    std::string _errMsg;
};
}  // namespace msgHandler

#endif