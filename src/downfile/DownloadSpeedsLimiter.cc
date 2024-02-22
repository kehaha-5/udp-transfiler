#include <chrono>
#include <thread>
#include "Constant.h"

#include "DownloadSpeedsLimiter.h"

using namespace downfile;

void DownloadSpeedsLimiter::waiting() {
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);
    auto durationMs = duration.count();
    if ((durationMs + _interruptionDurationMs) < 1000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 - (durationMs + _interruptionDurationMs)));
    }
    Clear();
}

void DownloadSpeedsLimiter::interruption() {
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);
    _interruptionDurationMs += duration.count();
}

bool DownloadSpeedsLimiter::allowSend(){
    return _canSendPacketsNum > 0;
}

void DownloadSpeedsLimiter::hasSend(){
    _canSendPacketsNum--;
}

void DownloadSpeedsLimiter::Clear(){
    _canSendPacketsNum = MAX_SEND_PACKETS;
    _interruptionDurationMs = 0;
}
