#ifndef CORE_ACK_ACK_SET_H
#define CORE_ACK_ACK_SET_H

#include <sys/types.h>

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "Constant.h"
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
    bool delMsgByAck(const u_long &ack);
    const u_long getAckSetSzie() { return _ackMsgMap.size(); }
    ~AckSet() { _ackMsgMap.clear(); }
    std::condition_variable _ackLimitCv;
    std::mutex _limitCvLock;
    bool _waittingforCv;
    bool ackSizeFull() { return _ackMsgMap.size() >= MAX_ACK_SET_SIZE; };

   private:
    TimerPrt _timerPtr;
    AckMsgMap _ackMsgMap;
    std::mutex _ackMsgMapLock;
};

}  // namespace ack

#endif