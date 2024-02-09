#include <sys/epoll.h>

#include <cassert>
#include <cstddef>
#include <functional>

#include "EventLoop.h"
#include "Logging.h"
#include "timer/Timer.h"

EventLoop::EventLoop() {
    _epollFd = epoll_create(MAXEVENTS);
    exit_if(_epollFd == -1, "epoll_create error");
}

void EventLoop::addIo(int fd, ioCallBack cd, unsigned int mask) {
    epoll_event event;
    ioEvent ioEvent = {};
    if (mask & EPOLL_EVENTS::EPOLLIN) {
        ioEvent.rb = cd;
    }
    if (mask & EPOLL_EVENTS::EPOLLOUT) {
        ioEvent.wb = cd;
    }
    int op = EPOLL_CTL_ADD;
    if (auto it = _ioEvents.find(fd); it != _ioEvents.end()) {
        op = EPOLL_CTL_MOD;
        it->second = ioEvent;
    } else {
        _ioEvents.insert({fd, ioEvent});
    }
    event.events = mask;
    event.data.fd = fd;
    int res = epoll_ctl(_epollFd, op, fd, &event);
    exit_if(res == -1, "epoll_ctl");
}

void EventLoop::delIo(int fd) {
    epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL);
    _ioEvents.erase(fd);
}

void EventLoop::loop() {
    while (_isRunning) {
        epoll_event events[MAXEVENTS];
        int num = epoll_wait(_epollFd, events, MAXEVENTS,
                             -1);  // timeout 参数关系到定时器的超时时间，至少要与定时器时间一致，尽量不要设置为0，否则导致cpu一直轮询
        for (int i = 0; i < num; i++) {
            if (events[i].events & EPOLL_EVENTS::EPOLLIN) {
                auto it = _ioEvents.find(events[i].data.fd);
                it->second.rb();
            }
            if (events[i].events & EPOLL_EVENTS::EPOLLOUT) {
                auto it = _ioEvents.find(events[i].data.fd);
                it->second.wb();
            }
        }
    }
}

void EventLoop::handleTimer() {
    timer::TimerOutCb cbs = _timer->getOutTimer();
    for (timer::TimerCb cb : cbs) {
        cb();
    }
}

void EventLoop::startTimer() {
    if (_timer == nullptr) {
        _timer = new timer::Timer();
    }
    addIo(_timer->getTimerfd(), std::bind(&EventLoop::handleTimer, this), EPOLLIN);
}

void EventLoop::stopTimer() { delIo(_timer->getTimerfd()); }