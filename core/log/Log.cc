
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Log.h"

Log* Log::_log = nullptr;
logAppender::type Log::_appender = logAppender::console;
logLever::type Log::_lever = logLever::info;

void Log::setConfig(logConfig conf) {
    if (!_log) {
        _log = new Log();
    }
    _lever = conf.level;
    _appender = conf.appender;
}

bool Log::canAppend(logType::type type) {
    if (_lever == logLever::info) {
        if (type == logType::debug) {
            return false;
        }
    }
    return true;
}

std::string Log::getCurrTime() {
    std::time_t t = std::time(NULL);
    std::string mbstr;
    mbstr.resize(20);
    std::strftime(&mbstr[0], mbstr.size(), "%F-%T", std::localtime(&t));
    return mbstr;
}
