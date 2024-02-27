#ifndef SRC_DOWNFILE_DOWNLOAD_SPEEDS_LIMITER_H
#define SRC_DOWNFILE_DOWNLOAD_SPEEDS_LIMITER_H

#include <sys/types.h>

#include <chrono>

#include "Constant.h"
#include "config/ClientConfig.h"

namespace downfile {
class DownloadSpeedsLimiter {
   public:
    void start() { _start = std::chrono::system_clock::now(); };
    void waiting();
    void interruption();
    bool allowSend();
    void hasSend();
    void Clear();

   private:
    u_long getMaxSendPackets() {
        return (std::ceil(config::ClientConfig::getInstance().getMaxDownloadSpeeds() / MAX_FILE_DATA_SIZE) == 0
                    ? 1
                    : std::ceil(config::ClientConfig::getInstance().getMaxDownloadSpeeds() / MAX_FILE_DATA_SIZE));
    }
    u_long _canSendPacketsNum = getMaxSendPackets();
    std::chrono::time_point<std::chrono::system_clock> _start;
    long _interruptionDurationMs = 0;
};
}  // namespace downfile

#endif