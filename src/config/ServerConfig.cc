#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

#include "Logging.h"
#include "ServerConfig.h"

using namespace config;

ServerConfig& ServerConfig::getInstance() {
    static ServerConfig serverConfig;
    return serverConfig;
}

ServerConfig::ServerConfig() { setDefualtConfig(); }

void ServerConfig::setDefualtConfig() {
    _ip = "0.0.0.0";
    _port = 23111;
    _threadNum = 10;
}

void ServerConfig::setConfigFilePath(std::string filePath) {
    _filePath = filePath;
    if (!fs::exists(_filePath)) {
        fs::create_directories(_filePath);
        info_log("the file directoriey not exist,has create this file directoriey");
    }
}

void ServerConfig::setConfigFile(std::string filePath) {
    if (!fs::exists(filePath)) {
        warn_log("config file not exist !!! using defualt Configuration");
        return;
    }
    std::ifstream configFile(filePath, std::ios_base::in);
    if (!configFile.good()) {
        warn_log("config file can not be read!!! using defualt Configuration");
    }
    std::string line;
    while (std::getline(configFile, line)) {
        if (findStrContain(line, "ip")) {
            _ip = getConfigData(line);
            continue;
        }
        if (findStrContain(line, "filePath")) {
            _filePath = getConfigData(line);
            continue;
        }
        if (findStrContain(line, "port")) {
            if (!getIntConfigData<u_short>(line, _port)) {
                warn_log("port is not a number !!! using defualt Configuration");
            }
            continue;
        }
        if (findStrContain(line, "threadNum")) {
            if (!getIntConfigData<u_short>(line, _threadNum)) {
                warn_log("threadNum is not a number !!! using defualt Configuration");
            }
            continue;
        }
        line.clear();
    }
}

const fs::path& ServerConfig::getFilepath() {
    if (_filePath.string().empty()) {
        _filePath = "./upload";
    }
    if (!fs::exists(_filePath)) {
        fs::create_directories(_filePath);
        info_log("the file directoriey not exist,has create this file directoriey");
    }
    return _filePath;
}
