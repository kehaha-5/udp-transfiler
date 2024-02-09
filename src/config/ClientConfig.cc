#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

#include "ClientConfig.h"
#include "Logging.h"

using namespace config;
namespace fs = std::filesystem;

ClientConfig &ClientConfig::getInstance() {
    static ClientConfig ClientConfig;
    return ClientConfig;
}

ClientConfig::ClientConfig() { setDefualtConfig(); }

void ClientConfig::setDefualtConfig() {
    _config = {};
    _config.filePath = "./upload";
    _config.ip = "127.0.0.1";
    _config.port = 23111;
    _config.downloadthreadNum = 5;
}

void ClientConfig::setConfigFile(std::string filePath) {
    if (!fs::exists(filePath)) {
        warn_log("config file not exist !!! using defualt Configuration");
    }
    std::fstream configFile(filePath, std::ios_base::in);
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
            if (!fs::exists(_config.filePath)) {
                fs::create_directories(_config.filePath);
                info_log("the file directoriey not exist,has create this file directoriey");
            }
        }
        if (findStrContain(line, "port")) {
            if (!getIntConfigData(line, _config.port)) {
                warn_log("port is not a number !!! using defualt Configuration");
            }
        }
        if (findStrContain(line, "downloadthreadNum")) {
            if (!getIntConfigData(line, _config.downloadthreadNum)) {
                warn_log("downloadthreadNum is not a number !!! using defualt Configuration");
            }
        }
        line.clear();
    }
}
