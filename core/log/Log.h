#ifndef CORE_LOG_H
#define CORE_LOG_H

#include <string>
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

class Log {
   public:
    static void setConfig(logConfig conf);
    static bool canAppend(logType::type type);
    static std::string getCurrTime();
    void outLog(const char* msg);
    ~Log();

   private:
    Log() = default;
    static Log* _log;
    static std::ofstream _logfile;
    static logLever::type _lever;
    static logAppender::type _appender;
};

#endif