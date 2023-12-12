#include <sys/timerfd.h>
#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <list>
#include <memory>

#include "Logging.h"
#include "Timer.h"

using namespace timer;

Timer::Timer() {
    _timerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    exit_if(_timerfd == -1, "error in init timerfd");
    for (int i = 0; i < TimerOnceLoop; i++) {
        TimerWheelItem item = {};
        _timerWheel.push_back(item);
    }
    _currTimerWheelIt = _timerWheel.begin();
    struct itimerspec newTime;
    newTime.it_value = {1, 0};     // 超时时间 第一次超时时间
    newTime.it_interval = {1, 0};  // 定时器的间隔时间
    int res = timerfd_settime(_timerfd, 0, &newTime, nullptr);
    exit_if(res == -1, "init runAt settime error");
    _allTimerEven.resize(TimerOnceLoop);
}

void Timer::setTimer(__time_t sec, long int ms) {
    struct itimerspec newTime;
    auto nsec = ms * 1000 * 1000;
    newTime.it_value = {sec, nsec};     // 超时时间 第一次超时时间
    newTime.it_interval = {sec, nsec};  // 定时器的间隔时间
    int res = timerfd_settime(_timerfd, 0, &newTime, nullptr);
}

int Timer::runEvery(int timerout, TimerCb cb) {
    TimerEvenSharedPtr even = std::make_shared<timerEven>();
    even->timeout = timerout % TimerOnceLoop;
    even->interval = true;
    even->cd = cb;
    runAfter(even);
    int index = _currTimerIndex++;
    _allTimerEven[index] = even;
    return index;
}

int Timer::runAt(TimerCb cb) {
    TimerEvenSharedPtr even = std::make_shared<timerEven>();
    even->timeout = 1;
    even->interval = true;
    even->cd = cb;
    runAfter(even);
    int index = _currTimerIndex++;
    _allTimerEven[index] = even;
    return index;
}

int Timer::runAfter(int timerout, TimerCb cb) {
    TimerEvenSharedPtr even = std::make_shared<timerEven>();
    even->timeout = timerout % TimerOnceLoop;
    even->interval = false;
    even->cd = cb;
    runAfter(even);
    int index = _currTimerIndex++;
    _allTimerEven[index] = even;
    return index;
}

void Timer::runAfter(TimerEvenSharedPtr even) {
    even->loop = even->timeout / TimerOnceLoop;
    if (even->timeout == 0) {
        even->loop = 1;
    }
    int itDistance = std::distance(_currTimerWheelIt, _timerWheel.end());
    TimerWheel::iterator insertIt;
    if (even->timeout > itDistance) {
        insertIt = _timerWheel.begin();
        std::advance(insertIt, (even->timeout - itDistance));
    } else if (even->timeout == TimerOnceLoop) {
        insertIt = _currTimerWheelIt;
    } else if (even->timeout == itDistance) {
        if (itDistance == 1) {
            insertIt = _timerWheel.begin();
        } else {
            insertIt = std::next(_currTimerWheelIt, (even->timeout - 1));
        }
    } else {
        insertIt = std::next(_currTimerWheelIt, even->timeout);
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
