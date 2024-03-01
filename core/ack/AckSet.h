#ifndef CORE_ACK_ACK_SET_H
#define CORE_ACK_ACK_SET_H

#include <sys/types.h>

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "config/ClientConfig.h"
#include "timer/Timer.h"

namespace ack {

typedef std::unordered_map<u_long, u_long> AckMsgMap;  // map [ack=>timerIndex]
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
    bool _waittingforCv = false;
    bool ackSizeFull() { return _ackMsgMap.size() >= config::ClientConfig::getInstance().getMaxAckSet(); };
    void clear() {
        _ackMsgMap.clear();
        _timerPtr->clearAllTimer();
    }

   private:
    TimerPrt _timerPtr;
    AckMsgMap _ackMsgMap;
    std::mutex _ackMsgMapLock;
};

}  // namespace ack

#endif