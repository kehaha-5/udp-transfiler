#ifndef SRC_CONFIG_CLIENT_CONFIG_H
#define SRC_CONFIG_CLIENT_CONFIG_H
#include <sys/types.h>

#include <string>

#include "config/Config.h"
namespace config {

struct clientConfig {
    std::string ip;
    u_short port;
    std::string filePath;
    u_short downloadthreadNum;
};

class ClientConfig : public Config {
   public:
    static ClientConfig &getInstance();
    void setConfigFile(std::string filePath);
    const clientConfig &getConfig() { return _config; };

   private:
    void setDefualtConfig();
    ClientConfig();
    clientConfig _config;
};
}  // namespace config

#endif