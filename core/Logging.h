#ifndef LOGGING_H
#define LOGGING_H
#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "log/Log.h"

inline void LOG(logType::type type, const char* fileName, const char* func, int line, const char* format, ...) {
    if (!Log::getLog().canAppend(type)) return;
    char msg[8192] = {0};
    std::string logType;
    switch (type) {
        case logType::warn:
            logType = "WARN";
            break;
        case logType::info:
            logType = "INFO";
            break;
        case logType::res:
            logType = "RES";
            break;
        default:
            logType = "DEBUG";
    }
    auto time = Log::getCurrTime();
#ifdef DEBUG  // no debug
    std::snprintf(msg, sizeof(msg), "%s %s %s %s:%d | ", time.c_str(), logType.c_str(), fileName, func, line);
#else
    std::snprintf(msg, sizeof(msg), "%s %s %d | ", time.c_str(), logType.c_str(), line);
#endif
    std::va_list args;
    va_start(args, format);
    std::vsprintf(msg + strlen(msg), format, args);
    va_end(args);
    Log::getLog().outLog(msg);
}

inline void IFEXIT(bool condition, const char* fileName, const char* func, int line, const char* format, ...) {
    if (condition) {
        char msg[4096] = {0};
        std::va_list args;
        va_start(args, format);
        auto time = Log::getCurrTime();
#ifdef DEBUG  // debug
        std::sprintf(msg, "ERROR %s %s %s:%d | ", time.c_str(), fileName, func, line);
#endif
        std::vsprintf(msg + strlen(msg), format, args);
        if (errno) {
            std::sprintf(msg + strlen(msg), "| errno %s", strerror(errno));
        }
        va_end(args);
        std::fprintf(stderr, "%s\n", msg);
        exit(EXIT_FAILURE);
    }
}
#define info_log(args...) LOG(logType::info, __FILE__, __func__, __LINE__, ##args);
#define res_log(args...) LOG(logType::res, __FILE__, __func__, __LINE__, ##args);
#define warn_log(args...) LOG(logType::warn, __FILE__, __func__, __LINE__, ##args);
#define debug_log(args...) LOG(logType::debug, __FILE__, __func__, __LINE__, ##args);
#define exit_if(condition, args...) IFEXIT(condition, __FILE__, __func__, __LINE__, ##args);
#define exit_log(args...) IFEXIT(true, __FILE__, __func__, __LINE__, ##args);

#endif