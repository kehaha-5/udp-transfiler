
#include <sys/epoll.h>

#include <functional>

#include "EventLoop.h"
#include "Logging.h"

EventLoop::EventLoop() {
    _epollFd = epoll_create(MAXEVENTS);
    exit_if(_epollFd == -1, "epoll_create error");
}

void EventLoop::addIo(int fd, ioCallBack cd, EPOLL_EVENTS mask) {
    epoll_event event;
    if (mask == EPOLL_EVENTS::EPOLLIN) {
        _rb = cd;
    }
    if (mask == EPOLL_EVENTS::EPOLLOUT) {
        _wb = cd;
    }
    // event.events = mask ;
    event.events = mask | EPOLLET;  //避免惊群
    int res = epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &event);
    exit_if(res == -1, "epoll_ctl");
}

void EventLoop::loop() {
    while (true) {
        epoll_event events[MAXEVENTS];
        int num = epoll_wait(_epollFd, events, MAXEVENTS, 10);
        for (int i = 0; i < num; i++) {
            if (events[i].events == EPOLL_EVENTS::EPOLLIN) {
                _rb();
            }
            if (events[i].events == EPOLL_EVENTS::EPOLLOUT) {
                _wb();
            }
        }
    }
}