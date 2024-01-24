#ifndef TIMER_H
#define TIMER_H

#include <bits/types/struct_timespec.h>
#include <sys/types.h>
#include <unistd.h>

#include <atomic>
#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace timer {

struct timerEven;
typedef std::weak_ptr<timerEven> TimerEvenWeakPtr;
typedef std::shared_ptr<timerEven> TimerEvenSharedPtr;
typedef std::list<TimerEvenWeakPtr> TimerWheelItem;
typedef std::list<TimerWheelItem> TimerWheel;
typedef std::function<void()> TimerCb;
typedef std::vector<TimerCb> TimerOutCb;
typedef std::vector<TimerEvenSharedPtr> AllTimerEven;

struct timerEven {
    TimerCb cd;
    u_long timeout;  //设置的超时时间 单位ms
    u_long loop;     //循环次数
    bool interval;
};

class Timer {
   public:
    Timer();
    ~Timer() {
        close(_timerfd);
        _allTimerEven.clear();
        _allTimerEven.shrink_to_fit();
    };
    int getTimerfd() { return _timerfd; };
    u_long runEvery(u_long timeroutMs, TimerCb cb);
    u_long runAfter(u_long timeroutMs, TimerCb cb);
    u_long runAt(TimerCb cb);
    void cancelTimerEven(int index) { _allTimerEven[index].reset(); };
    TimerOutCb getOutTimer();
    void setIntervalTimer(__time_t second, long int ms);
    u_long getIntervalTimer() { return _intervalMs; }

   private:
    void resetTimer();
    void runAfter(TimerEvenSharedPtr even);
    int _timerfd;
    TimerWheel _timerWheel;
    TimerWheel::iterator _currTimerWheelIt;
    AllTimerEven _allTimerEven;
    std::atomic_uint _currTimerIndex = 0;
    u_short _intervalMs = 100;                  //默认每次触发时间 ms
    u_long _timerOnceLoop = _intervalMs * 10;  //一次循环的总时间单位ms
};
}  // namespace timer

#endif