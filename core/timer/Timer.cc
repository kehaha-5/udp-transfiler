#include <sys/timerfd.h>
#include <sys/types.h>
#include <unistd.h>

#include <iterator>
#include <list>
#include <memory>

#include "Logging.h"
#include "Timer.h"

using namespace timer;

Timer::Timer() {
    _timerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    exit_if(_timerfd == -1, "error in init timerfd");
    for (int i = 0; i < 10; i++) {
        TimerWheelItem item = {};
        _timerWheel.push_back(item);
    }
    _currTimerWheelIt = _timerWheel.begin();
    struct itimerspec newTime;
    auto tenMs = _intervalMs * 1000 * 1000;  // 10ms 触发一次
    newTime.it_value = {0, tenMs};           // 超时时间 第一次超时时间
    newTime.it_interval = {0, tenMs};        // 定时器的间隔时间
    int res = timerfd_settime(_timerfd, 0, &newTime, nullptr);
    exit_if(res == -1, "init runAt settime error");
    _allTimerEven.resize(10);
}
void Timer::setIntervalTimer(__time_t sec, long int ms) {
    struct itimerspec newTime;
    auto nsec = ms * 1000 * 1000;
    newTime.it_value = {sec, nsec};     // 超时时间 第一次超时时间
    newTime.it_interval = {sec, nsec};  // 定时器的间隔时间
    int res = timerfd_settime(_timerfd, 0, &newTime, nullptr);
    _intervalMs = ms + (sec * 1000);
    _timerOnceLoop = _intervalMs * 10;
    exit_if(res == -1, "init runAt settime error");
}

u_long Timer::runEvery(u_long timerout, TimerCb cb) {
    TimerEvenSharedPtr even = std::make_shared<timerEven>();
    even->timeout = timerout;
    even->interval = true;
    even->cd = cb;
    runAfter(even);
    int index = _currTimerIndex++;
    _allTimerEven[index] = even;
    return index;
}

u_long Timer::runAt(TimerCb cb) {
    TimerEvenSharedPtr even = std::make_shared<timerEven>();
    even->timeout = 10;
    even->interval = true;
    even->cd = cb;
    runAfter(even);
    int index = _currTimerIndex++;
    _allTimerEven[index] = even;
    return index;
}

u_long Timer::runAfter(u_long timerout, TimerCb cb) {
    TimerEvenSharedPtr even = std::make_shared<timerEven>();
    even->timeout = timerout;
    even->interval = false;
    even->cd = cb;
    runAfter(even);
    int index = _currTimerIndex++;
    _allTimerEven[index] = even;
    return index;
}

void Timer::runAfter(TimerEvenSharedPtr even) {
    even->loop = even->timeout / _timerOnceLoop;
    auto pos = even->timeout % _timerOnceLoop / _intervalMs;  //要被添加到时间轮里面的位置
    int itDistance = std::distance(_currTimerWheelIt, _timerWheel.end());
    TimerWheel::iterator insertIt;
    if (pos > itDistance) {
        insertIt = _timerWheel.begin();
        std::advance(insertIt, (pos - itDistance));
    } else if (pos == 0) {
        insertIt = _currTimerWheelIt;
    } else if (pos == itDistance) {
        if (itDistance == 1) {
            insertIt = _timerWheel.begin();
        } else {
            insertIt = std::next(_currTimerWheelIt, (pos - 1));
        }
    } else {
        insertIt = std::next(_currTimerWheelIt, pos);
    }
    insertIt->push_back(even);
}

TimerOutCb Timer::getOutTimer() {
    TimerOutCb item;
    std::list<TimerWheelItem::iterator> wheelDelItem;
    uint64_t val;
    read(_timerfd, &val, sizeof(val));
    for (auto it = _currTimerWheelIt->begin(); it != _currTimerWheelIt->end(); it++) {
        auto itt = it->lock();
        if (itt == nullptr) {
            wheelDelItem.push_back(it);
            continue;
        }
        if (itt->loop == 0) {
            item.push_back(itt->cd);
            if (itt->interval) {
                runAfter(itt);
            }
            wheelDelItem.push_back(it);
        } else {
            itt->loop--;
        }
    }
    for (auto it = wheelDelItem.begin(); it != wheelDelItem.end(); it++) {
        _currTimerWheelIt->erase(*it);
    }
    _currTimerWheelIt++;
    if (_currTimerWheelIt == _timerWheel.end()) {
        _currTimerWheelIt = _timerWheel.begin();
    }
    return item;
}
