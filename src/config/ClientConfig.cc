#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

#include "ClientConfig.h"
#include "Logging.h"

using namespace config;
namespace fs = std::filesystem;

ClientConfig& ClientConfig::getInstance() {
    static ClientConfig ClientConfig;
    return ClientConfig;
}

ClientConfig::ClientConfig() { setDefualtConfig(); }

void ClientConfig::setDefualtConfig() {
    _ip = "127.0.0.1";
    _port = 23111;
    _downloadThreadNum = 5;
}

void ClientConfig::setConfigFile(std::string filePath) {
    if (!fs::exists(filePath)) {
        warn_log("config file not exist !!! using defualt Configuration");
        return;
    }
    std::fstream configFile(filePath, std::ios_base::in);
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
            if (!fs::exists(_filePath)) {
                fs::create_directories(_filePath);
                info_log("the file directoriey not exist,has create this file directoriey");
            }
        }
        if (findStrContain(line, "port")) {
            if (!getIntConfigData(line, _port)) {
                warn_log("port is not a number !!! using defualt Configuration");
            }
        }
        if (findStrContain(line, "downloadThreadNum")) {
            if (!getIntConfigData(line, _downloadThreadNum)) {
                warn_log("downloadThreadNum is not a number !!! using defualt Configuration");
            }
        }
        line.clear();
    }
}
void ClientConfig::setConfigFilePath(std::string filePath) {
    _filePath = filePath;
    if (!fs::exists(_filePath)) {
        fs::create_directories(_filePath);
        info_log("the file directoriey not exist,has create this file directoriey");
    }
}

const fs::path& ClientConfig::getFilepath() {
    if (_filePath.string().empty()) {
        _filePath = "./downloadfile";
    }
    if (!fs::exists(_filePath)) {
        fs::create_directories(_filePath);
        info_log("the file directoriey not exist,has create this file directoriey");
    }
    return _filePath;
}