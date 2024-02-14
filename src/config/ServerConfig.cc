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
    _threadNum = 5;
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
        }
        if (findStrContain(line, "filePath")) {
            _filePath = getConfigData(line);
        }
        if (findStrContain(line, "port")) {
            if (!getIntConfigData(line, _port)) {
                warn_log("port is not a number !!! using defualt Configuration");
            }
        }
        if (findStrContain(line, "threadNum")) {
            if (!getIntConfigData(line, _threadNum)) {
                warn_log("threadNum is not a number !!! using defualt Configuration");
            }
        }
        line.clear();
    }
}

const fs::path& ServerConfig::getFilepath() {
    if (_filePath.string().empty()) {
        _filePath = "./download";
    }
    if (!fs::exists(_filePath)) {
        fs::create_directories(_filePath);
        info_log("the file directoriey not exist,has create this file directoriey");
    }
    return _filePath;
}
