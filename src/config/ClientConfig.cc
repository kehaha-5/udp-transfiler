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

ClientConfig::ClientConfig() { setDefaultConfig(); }
void ClientConfig::setDefaultConfig() {
    _ip = "127.0.0.1";
    _port = 23111;
    _downloadThreadNum = 1;
    _packetsTimerOut = 1000;
    _maxDownloadSpeeds = 1024 * 1024 * 10;
    _maxAckSet = 500;
}

void ClientConfig::setConfigFile(std::string filePath) {
    if (!fs::exists(filePath)) {
        warn_log("config file not exist !!! using default Configuration");
        return;
    }
    std::fstream configFile(filePath, std::ios_base::in);
    if (!configFile.good()) {
        warn_log("config file can not be read!!! using default Configuration");
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
            if (getConfigData<fs::path>(line, _filePath)) {
                if (!fs::exists(_filePath)) {
                    fs::create_directories(_filePath);
                    info_log("the file directoriey not exist,has create this file directoriey");
                }
            } else {
                warn_log("filePath is empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "port")) {
            if (!getConfigData(line, _port)) {
                warn_log("port is not a number or empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "downloadThreadNum")) {
            if (!getConfigData<u_short>(line, _downloadThreadNum)) {
                warn_log("downloadThreadNum is not a number or empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "packetsTimerOut")) {
            if (!getConfigData<u_short>(line, _packetsTimerOut)) {
                warn_log("packetsTimerOut is not a number or empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "maxDownloadSpeeds")) {
            if (!getConfigData<uint>(line, _maxDownloadSpeeds)) {
                warn_log("maxDownloadSpeeds is not a number or empty !!! using default Configuration");
            }
            continue;
        }
        if (findStrContain(line, "maxResendPacketsNum")) {
            if (!getConfigData<uint>(line, _maxAckSet)) {
                warn_log("maxAckSet is not a number or empty !!! using default Configuration");
            }
            continue;
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