#include <sys/epoll.h>

#include <functional>

#include "EventLoop.h"
#include "Logging.h"
#include "timer/Timer.h"

EventLoop::EventLoop() {
    _epollFd = epoll_create(MAXEVENTS);
    exit_if(_epollFd == -1, "epoll_create error");
    _timer = new timer::Timer();
    addIo(_timer->getTimerfd(), std::bind(&EventLoop::handleTimer, this), EPOLLIN);
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

void EventLoop::loop() {
    while (_isRunning) {
        epoll_event events[MAXEVENTS];
        int num = epoll_wait(_epollFd, events, MAXEVENTS, 0);
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
    debug_log("handleTimer");
    timer::TimerOutCb cbs = _timer->getOutTimer();
    for (timer::TimerCb cb : cbs) {
        cb();
    }
}