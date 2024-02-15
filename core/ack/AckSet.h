#ifndef CORE_ACK_ACK_SET_H
#define CORE_ACK_ACK_SET_H

#include <sys/types.h>

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "timer/Timer.h"

namespace ack {

typedef std::unordered_map<u_long, u_long> AckMsgMap;
typedef std::function<void()> Cb;
typedef std::shared_ptr<timer::Timer> TimerPrt;

class AckSet {
   public:
    AckSet(TimerPrt timerPtr) : _timerPtr(timerPtr) {}
    u_long getAck();
    void setCbByAck(u_long &ack, Cb cb);
    void delMsgByAck(const u_long &ack);
    ~AckSet() { _ackMsgMap.clear(); }

   private:
    TimerPrt _timerPtr;
    AckMsgMap _ackMsgMap;
    std::mutex _ackMsgMapLock;
};

}  // namespace ack

#endif