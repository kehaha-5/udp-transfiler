#ifndef SRC_CONFIG_SERVER_CONFIG_H
#define SRC_CONFIG_SERVER_CONFIG_H
#include <sys/types.h>

#include <string>

#include "config/Config.h"
namespace config {

struct serverConfig {
    std::string ip;
    u_short port;
    std::string filePath;
    u_short threadNum;
};

class ServerConfig : public Config {
   public:
    static ServerConfig &getInstance();
    void setConfigFile(std::string filePath);
    const serverConfig &getConfig() { return _config; };

   private:
    void setDefualtConfig();
    ServerConfig();
    serverConfig _config;
};
}  // namespace config

#endif