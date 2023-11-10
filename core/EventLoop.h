#ifndef CORE_EVENTLOOP_H
#define CORE_EVENTLOOP_H
#include <sys/epoll.h>

#include <functional>
#include <memory>

#define MAXEVENTS 100

typedef std::function<void()> ioCallBack;

struct ioEvent {
    EPOLL_EVENTS mask;
    ioCallBack rb;
    ioCallBack wb;
};

class EventLoop {
   public:
    EventLoop();
    ~EventLoop() = default;
    void addIo(int fd, ioCallBack cd, EPOLL_EVENTS mask);
    void delIo(int fd);
    void loop();
    void runAfer();
    void runEvey();
    void runAt();

   private:
    int _epollFd;
    ioCallBack _rb;
    ioCallBack _wb;
};
#endif