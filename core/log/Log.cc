
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

#include "Constant.h"
#include "Log.h"

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
        _logThread = std::thread(std::bind(&Log::writeLogToFile, this));
        _logThread.detach();
    }
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
    std::string mbstr(50, 0);
    std::strftime(&mbstr[0], mbstr.size(), "%F-%T", std::localtime(&t));
    return mbstr;
}

void Log::outLog(const char* msg) {
    if (_appender == logAppender::file) {
        {
            std::unique_lock<std::mutex> lk(_logLock);
            _logMsg.push(std::string(msg));
            _logThreadCV.notify_one();
        }
    } else {
        std::fprintf(stdout, "%s\n", msg);
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

void Log::writeLogToFile() {
    std::unique_lock<std::mutex> lk(_logLock);
    _logThreadCV.wait(lk, [this]() { return !_logMsg.empty(); });
    while (!_logMsg.empty()) {
        _logfile << _logMsg.front().c_str() << std::endl;
        _logMsg.pop();
    }
    _logfile.flush();
}
