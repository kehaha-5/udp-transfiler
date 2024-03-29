#ifndef CORE_EVENTLOOP_H
#define CORE_EVENTLOOP_H
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>

#include <cassert>
#include <functional>
#include <memory>

#include "timer/Timer.h"
#define MAXEVENTS 10000

struct ioEvent;
typedef std::function<void()> ioCallBack;
typedef std::unordered_map<int, ioEvent> IoEvents;
typedef std::shared_ptr<timer::Timer> TimerPtr;

struct ioEvent {
    ioCallBack rb;
    ioCallBack wb;
};

class EventLoop {
   public:
    EventLoop();
    ~EventLoop() { close(_epollFd); };
    void addIo(int fd, ioCallBack cd, unsigned int mask);  // modify io cb fun by this fun
    void delIo(int fd);
    void loop();
    void setRunning(bool running) { _isRunning = running; };

    u_long runAfter(u_long timerout, timer::TimerCb cb) { return _timer->runAfter(timerout, cb); };
    u_long runEvery(u_long timerout, timer::TimerCb cb) { return _timer->runEvery(timerout, cb); };
    u_long runAt(timer::TimerCb cb) { return _timer->runAt(cb); };
    void cancelTimerEven(int Timerindex) { _timer->cancelTimerEven(Timerindex); };
    u_long getIntervalTimer() { return _timer->getIntervalTimer(); }
    void handleTimer();
    void startTimer();
    void stopTimer();
    bool isRunning() { return _isRunning; }
    TimerPtr getTimer() {
        assert(_timer);
        return _timer;
    }

   private:
    int _epollFd;
    TimerPtr _timer;
    IoEvents _ioEvents;
    ioCallBack _timerCb;
    bool _isRunning = true;
};
#endif