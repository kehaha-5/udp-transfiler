#ifndef CORE_EVENTLOOP_H
#define CORE_EVENTLOOP_H
#include <sys/epoll.h>

#include <functional>
#include <memory>

#include "udp/UpdServer.h"

#define MAXEVENTS 100

typedef void ioCallBack(void* args);

struct ioEvent {
    EPOLL_EVENTS mask;
    ioCallBack* rb;
    ioCallBack* wb;
    void* rbArgs;
    void* wbArgs;
};

class EventLoop {
   public:
    EventLoop();
    ~EventLoop() = default;
    void addIo(int fd, ioCallBack cd, EPOLL_EVENTS mask, void* args);
    void delIo(int fd);
    void loop();
    void runAfer();
    void runEvey();
    void runAt();

   private:
    int epollFd;
    ioCallBack rb;
    ioCallBack wb;
};
#endif