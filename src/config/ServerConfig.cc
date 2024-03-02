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

ServerConfig::ServerConfig() { setDefaultConfig(); }

void ServerConfig::setDefaultConfig() {
    _ip = "0.0.0.0";
    _port = 23111;
    _threadNum = 10;
    setDefaultFilePath();
}

void ServerConfig::setDefaultFilePath() { setConfigFile("./upload"); }

void ServerConfig::setConfigFilePath(std::string filePath) {
    _filePath = filePath;
    if (!fs::exists(_filePath)) {
        fs::create_directories(_filePath);
        info_log("the file directoriey not exist,has create this file directoriey");
    }
}

void ServerConfig::setConfigFile(std::string filePath) {
    if (!fs::exists(filePath)) {
        warn_log("config file not exist !!! using default Configuration");
        return;
    }
    std::ifstream configFile(filePath, std::ios_base::in);
    if (!configFile.good()) {
        warn_log("config file can not be read!!! using default Configuration");
        return;
    }
    std::string line;
    while (std::getline(configFile, line)) {
        if (findStrContain(line, "ip")) {
            std::string ip;
            if (!getConfigData<std::string>(line, ip)) {
                warn_log("ip is empty !!! using default Configuration");
            }
            if (isIpformat(ip)) {
                _ip = ip;
            } else {
                warn_log("it is not ip format !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "filePath")) {
            if (!getConfigData<fs::path>(line, _filePath)) {
                warn_log("filePath is empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "port")) {
            if (!getConfigData<u_short>(line, _port)) {
                warn_log("port is not a number or empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "threadNum")) {
            if (!getConfigData<u_short>(line, _threadNum)) {
                warn_log("threadNum is not a number !!! using default Configuration");
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
