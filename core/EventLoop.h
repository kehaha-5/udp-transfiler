#ifndef CORE_EVENTLOOP_H
#define CORE_EVENTLOOP_H
#include <sys/epoll.h>
#include <unistd.h>

#include <functional>
#include <memory>

#include "timer/Timer.h"
#define MAXEVENTS 100

struct ioEvent;
typedef std::function<void()> ioCallBack;
typedef std::unordered_map<int, ioEvent> IoEvents;

struct ioEvent {
    ioCallBack rb;
    ioCallBack wb;
};

class EventLoop {
   public:
    EventLoop();
    ~EventLoop() { close(_epollFd); };
    void addIo(int fd, ioCallBack cd, EPOLL_EVENTS mask);
    void delIo(int fd);
    void loop();
    int runAfter(int timerout, timer::TimerCb cb) { return _timer.runAfter(timerout, cb); };
    int runEvery(int timerout, timer::TimerCb cb) { return _timer.runEvery(timerout, cb); };
    int runAt(timer::TimerCb cb) { return _timer.runAt(cb); };
    void cancelTimerEven(int Timerindex) { _timer.cancelTimerEven(Timerindex); };
    void handleTimer();

   private:
    int _epollFd;
    timer::Timer _timer;
    IoEvents _ioEvents;
    ioCallBack _timerCb;
};
#endif