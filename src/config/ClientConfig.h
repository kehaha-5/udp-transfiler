#ifndef SRC_CONFIG_CLIENT_CONFIG_H
#define SRC_CONFIG_CLIENT_CONFIG_H
#include <sys/types.h>

#include <filesystem>
#include <string>

#include "config/Config.h"
namespace config {

namespace fs = std::filesystem;

class ClientConfig : public Config {
   public:
    static ClientConfig& getInstance();
    void setConfigFile(std::string filePath);
    void setConfigFilePath(std::string filePath);
    void setConfigIp(std::string ip) { _ip = ip; }
    void setConfigPort(u_short port) { _port = port; }
    void setConfigDownloadThreadNum(u_short downloadthreadNum) { _downloadThreadNum = downloadthreadNum; }
    const fs::path& getFilepath();
    const u_short& getPort() { return _port; }
    const u_short& getDownloadThreadNum() { return _downloadThreadNum; }
    const u_short& getPacketsTimerOut() { return _packetsTimerOut; }
    const std::string& getIp() { return _ip; }
    const uint& getMaxDownloadSpeeds() { return _maxDownloadSpeeds; }
    const uint& getMaxAckSet() { return _maxAckSet; }


   private:
    void setDefualtConfig();
    ClientConfig();
    std::string _ip;
    u_short _port;
    fs::path _filePath;
    u_short _downloadThreadNum;
    u_short _packetsTimerOut;
    uint _maxDownloadSpeeds;
    uint _maxAckSet;
};
}  // namespace config

#endif