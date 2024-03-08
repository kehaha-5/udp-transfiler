
#include <sys/time.h>

#include <chrono>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

#include "Constant.h"
#include "Log.h"
#include "config/ServerConfig.h"

Log& Log::getLog() {
    static Log log;
    return log;
}

void Log::setConfig(logConfig conf) {
    if (!_init) {
        _init = true;
    }
    _lever = conf.level;
    _appender = conf.appender;
    if (conf.appender == logAppender::file) {
        if (!std::filesystem::exists(LOG_DIR)) {
            std::filesystem::create_directory(LOG_DIR);
        }
        auto logfile = std::filesystem::path(LOG_DIR) / (getLogfileName() + LOG_FILE_SUFFIX);
        _logfile.open(logfile);
        _logThread = std::thread(std::bind(&Log::writeLog, this));
        _logThread.detach();
    }
}

bool Log::canAppend(logType::type type) {
    if (type == logType::res && !config::ServerConfig::getInstance().getIsShowResLog()) {
        return false;
    }
    if (_lever == logLever::info) {
        if (type == logType::debug) {
            return false;
        }
    }
    return true;
}

const std::string Log::getCurrTime() {
    struct timeval current_time;
    gettimeofday(&current_time, 0);
    return Log::getLog().getCurrTime(current_time);
}

void Log::outLog(const char* msg) {
    if (logAppender::console == _appender) {
        std::fprintf(stdout, "%s\n", msg);
    } else {
        std::unique_lock<std::mutex> lk(_logLock);
        _logMsg.push(msg);
        _logThreadCV.notify_one();
    }
}

std::string Log::getLogfileName() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    // Convert the `time_point` object to a `time_t` value.
    time_t timestamp = std::chrono::system_clock::to_time_t(now);
    // Convert the `time_t` value to milliseconds.
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::to_string(milliseconds) + "-";
}

void Log::writeLog() {
    while (true) {
        std::unique_lock<std::mutex> lk(_logLock);
        _logThreadCV.wait(lk, [this]() { return (!_logMsg.empty()) || (!_isRunning); });
        while (!_logMsg.empty()) {
            _logfile << _logMsg.front() << std::endl;
            _logMsg.pop();
        }
        _logfile.flush();
        if (!_isRunning) {
            return;
        }
    }
}

const std::string Log::getCurrTime(const timeval& time) {
    struct tm local_tm;
    localtime_r(&time.tv_sec, &local_tm);
    std::string time_str(100, '\0');
    std::sprintf(&time_str[0], "%04d-%02d-%02d %02d:%02d:%02d.%06ld", local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday,
                 local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec, (long)time.tv_usec);
    return time_str;
}
