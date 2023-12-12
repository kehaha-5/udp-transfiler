#ifndef TIMER_H
#define TIMER_H

#include <bits/types/struct_timespec.h>
#include <unistd.h>

#include <atomic>
#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace timer {
const int TimerOnceLoop = 10;
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
    int timeout;
    int loop;
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
    int runEvery(int timerout, TimerCb cb);
    int runAfter(int timerout, TimerCb cb);
    int runAt(TimerCb cb);
    void cancelTimerEven(int index) { _allTimerEven[index].reset(); };
    TimerOutCb getOutTimer();
    void setTimer(__time_t second, long int ms);

   private:
    void resetTimer();
    void runAfter(TimerEvenSharedPtr even);
    int _timerfd;
    TimerWheel _timerWheel;
    TimerWheel::iterator _currTimerWheelIt;
    AllTimerEven _allTimerEven;
    std::atomic_uint _currTimerIndex = 0;
};
}  // namespace timer

#endif