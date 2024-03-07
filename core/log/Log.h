#ifndef CORE_LOG_H
#define CORE_LOG_H

#include <bits/types/struct_timeval.h>

#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

struct logLever {
    enum type {
        info = 1,  //可以输出 info warn
        debug,     //可以输出除info等级以外再加上 debug
    };
};

struct logType {
    enum type { warn, info, debug };
};

struct logAppender {
    enum type {
        console = 1,
        file,
    };
};

struct logConfig {
    logConfig(logLever::type _level, logAppender::type _appender) : level(_level), appender(_appender) {}
    logLever::type level;
    logAppender::type appender;
};

struct logMsgItem {
    logMsgItem(timeval _time, std::string _msg) : time(_time), msg(_msg){};
    timeval time;
    std::string msg;
};

typedef std::queue<logMsgItem> logMsg;

class Log {
   public:
    static Log& getLog();
    void setConfig(logConfig conf);
    bool canAppend(logType::type type);
    static const std::string getCurrTime();
    const std::string getCurrTime(const timeval& time);
    void outLog(const char* msg);
    ~Log() {
        _isRunning = false;
        _logThreadCV.notify_one();
    }

   private:
    std::string getLogfileName();
    std::string getLogMsgBylogMsgItem(const logMsgItem& item);
    void writeLog();
    Log() = default;
    bool _init = false;
    std::ofstream _logfile;
    logLever::type _lever;
    logAppender::type _appender;
    logMsg _logMsg;
    std::thread _logThread;
    std::condition_variable _logThreadCV;
    std::mutex _logLock;
    bool _isRunning = true;
};

#endif