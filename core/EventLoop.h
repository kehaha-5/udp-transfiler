#ifndef CORE_EVENTLOOP_H
#define CORE_EVENTLOOP_H
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>

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
    ~EventLoop() {
        close(_epollFd);
        delete _timer;
    };
    void addIo(int fd, ioCallBack cd, unsigned int mask);
    void delIo(int fd);
    void loop();
    void setRunning(bool running) { _isRunning = running; };

    u_long runAfter(u_long timerout, timer::TimerCb cb) { return _timer->runAfter(timerout, cb); };
    u_long runEvery(u_long timerout, timer::TimerCb cb) { return _timer->runEvery(timerout, cb); };
    u_long runAt(timer::TimerCb cb) { return _timer->runAt(cb); };
    void cancelTimerEven(int Timerindex) { _timer->cancelTimerEven(Timerindex); };
    void setIntervalTimer(__time_t second, long int ms) { _timer->setIntervalTimer(second, ms); }
    u_long getIntervalTimer() { return _timer->getIntervalTimer(); }
    void handleTimer();
    void startTimer();
    void stopTimer();

   private:
    int _epollFd;
    timer::Timer* _timer = nullptr;
    IoEvents _ioEvents;
    ioCallBack _timerCb;
    bool _isRunning = true;
};
#endif