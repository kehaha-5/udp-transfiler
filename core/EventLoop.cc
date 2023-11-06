
#include <sys/epoll.h>

#include <functional>

#include "EventLoop.h"
#include "Logging.h"

EventLoop::EventLoop() {
    epollFd = epoll_create(MAXEVENTS);
    exit_if(epollFd == -1, "epoll_create error");
}

void EventLoop::addIo(int fd, ioCallBack cd, EPOLL_EVENTS mask, void* args) {
    ioEvent ioEvent;
    epoll_event event;
    if (mask == EPOLL_EVENTS::EPOLLIN) {
        ioEvent.rb = cd;
        ioEvent.rbArgs = args;
    }
    if (mask == EPOLL_EVENTS::EPOLLOUT) {
        ioEvent.wb = cd;
        ioEvent.wbArgs = args;
    }
    event.events = mask;
    ioEvent.mask = mask;
    event.data.ptr = &ioEvent;
    int res = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
    exit_if(res == -1, "epoll_ctl");
}

void EventLoop::loop() {
    while (true) {
        epoll_event events[MAXEVENTS];
        int num = epoll_wait(epollFd, events, MAXEVENTS, 10);
        for (int i = 0; i < num; i++) {
            if (events[i].events == EPOLL_EVENTS::EPOLLIN) {
                ioEvent* event = (ioEvent*)events[i].data.ptr;
                event->rb(event->rbArgs);
            }
        }
    }
}