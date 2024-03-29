#ifndef TIMER_H
#define TIMER_H

#include <bits/types/struct_timespec.h>
#include <sys/types.h>
#include <unistd.h>

#include <atomic>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace timer {

struct timerEven;
typedef std::weak_ptr<timerEven> TimerEvenWeakPtr;
typedef std::shared_ptr<timerEven> TimerEvenSharedPtr;
typedef std::list<TimerEvenWeakPtr> TimerWheelItem;
typedef std::list<TimerWheelItem> TimerWheel;
typedef std::function<void()> TimerCb;
typedef std::vector<TimerCb> TimerOutCb;
typedef std::unordered_map<uint, TimerEvenSharedPtr> AllTimerEven;

struct timerEven {
    TimerCb cd;
    u_long timeout;  // 设置的超时时间 单位ms
    u_long loop;     // 循环次数
    bool interval;
};

class Timer {
   public:
    Timer();
    ~Timer() {
        close(_timerfd);
        _allTimerEven.clear();
    };
    int getTimerfd() { return _timerfd; };
    uint runEvery(u_long timeroutMs, TimerCb cb);
    uint runAfter(u_long timeroutMs, TimerCb cb);
    uint runAt(TimerCb &cb);
    void cancelTimerEven(uint index) {
        _allTimerEven[index].reset();
        _allTimerEven.erase(index);
    };
    TimerOutCb getOutTimer();
    u_long getIntervalTimer() { return _intervalMs; }
    void clearAllTimer() { _allTimerEven.clear(); };

   private:
    void resetTimer();
    void runAfter(TimerEvenSharedPtr &even);
    int _timerfd;
    TimerWheel _timerWheel;
    TimerWheel::iterator _currTimerWheelIt;
    u_int _currTimerWheelIndex = 0;
    AllTimerEven _allTimerEven = {};
    std::atomic_uint _currTimerIndex = 0;
    u_short _intervalMs = 10;                  // 默认每次触发时间 ms
    u_long _timerOnceLoop = _intervalMs * 10;  // 一次循环的总时间单位ms
    std::recursive_mutex _timerWheelItLock;
};
}  // namespace timer

#endif