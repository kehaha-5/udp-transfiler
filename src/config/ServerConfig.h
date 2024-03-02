#ifndef SRC_CONFIG_SERVER_CONFIG_H
#define SRC_CONFIG_SERVER_CONFIG_H
#include <sys/types.h>

#include <string>
#include <filesystem>

#include "config/Config.h"
namespace config {

namespace fs = std::filesystem;

class ServerConfig : public Config {
   public:
    static ServerConfig &getInstance();
    void setConfigFile(std::string filePath);
    void setConfigFilePath(std::string filePath);
    void setConfigIp(std::string ip) { _ip = ip; }
    void setConfigPort(u_short port) { _port = port; }
    void setConfigThreadNum(u_short threadNum) { _threadNum = threadNum; }
    const fs::path& getFilepath();
    const u_short& getPort() { return _port; }
    const u_short& getThreadNum() { return _threadNum; }
    const std::string& getIp() { return _ip; }

   private:
    void setDefaultConfig();
    void setDefaultFilePath();
    ServerConfig();
    std::string _ip;
    u_short _port;
    fs::path _filePath;
    u_short _threadNum;
};
}  // namespace config

#endif