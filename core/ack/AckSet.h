#ifndef CORE_ACK_ACK_SET_H
#define CORE_ACK_ACK_SET_H

#include <sys/types.h>

#include <mutex>
#include <string>
#include <unordered_map>

namespace ack {

typedef std::unordered_map<u_long, std::string> AckMsgMap;

class AckSet {
   public:
    u_long getAck(std::string msg);
    std::string &getMsgByAck(u_long &ack);
    void delMsgByAck(const u_long &ack);
    ~AckSet() { _ackMsgMap.clear(); }

   private:
    AckMsgMap _ackMsgMap;
    std::mutex _ackMsgMapLock;
};

}  // namespace ack

#endif