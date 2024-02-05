#ifndef MSG_BUFFER_H
#define MSG_BUFFER_H

#include <sys/types.h>

#include "msg/Msg.h"
#include "msg/proto/package_msg.pb.h"

namespace msg {
class Buffer {
   public:
    void setData(Package& package);
    std::string& getData() { return _data; };
    u_short getSize() { return _hasRevLenght; }
    u_long getAck() { return _ack; }
    msg::proto::MsgType getMsgType() { return _msgType; }
    bool hasAllData() { return _hasRevLenght == _tatolLenght; }
    void clear();

   private:
    u_short _hasRevLenght = 0;
    u_short _tatolLenght = 0;
    u_long _ack = 0;
    msg::proto::MsgType _msgType;
    std::string _data;
    bool _init = false;
};
}  // namespace msg

#endif