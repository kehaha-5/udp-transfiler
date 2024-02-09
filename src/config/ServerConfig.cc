#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

#include "Logging.h"
#include "ServerConfig.h"

using namespace config;
namespace fs = std::filesystem;

ServerConfig &ServerConfig::getInstance() {
    static ServerConfig serverConfig;
    return serverConfig;
}

ServerConfig::ServerConfig() { setDefualtConfig(); }

void ServerConfig::setDefualtConfig() {
    _config = {};
    _config.filePath = "./upload";
    _config.ip = "0.0.0.0";
    _config.port = 23111;
    _config.threadNum = 5;
}

void ServerConfig::setConfigFile(std::string filePath) {
    if (!fs::exists(filePath)) {
        warn_log("config file not exist !!! using defualt Configuration");
    }
    std::ifstream configFile(filePath, std::ios_base::in);
    if (!configFile.good()) {
        warn_log("config file can not be read!!! using defualt Configuration");
    }
    std::string line;
    while (std::getline(configFile, line)) {
        if (findStrContain(line, "ip")) {
            _config.ip = getConfigData(line);
        }
        if (findStrContain(line, "filePath")) {
            _config.filePath = getConfigData(line);
        }
        if (findStrContain(line, "port")) {
            if (!getIntConfigData(line, _config.port)) {
                warn_log("port is not a number !!! using defualt Configuration");
            }
        }
        if (findStrContain(line, "threadNum")) {
            if (!getIntConfigData(line, _config.threadNum)) {
                warn_log("threadNum is not a number !!! using defualt Configuration");
            }
        }
        line.clear();
    }
}
