#include <sys/types.h>

#include <chrono>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <sstream>
#include <string>

#include "Directory.h"
#include "Logging.h"
#include "config/ServerConfig.h"
#include "file/FileHash.h"

using namespace file::server;

Directory &Directory::getInstance() {
    static Directory _self;
    return _self;
}

void Directory::setFilePath() {
    auto path = config::ServerConfig::getInstance().getFilepath();
    _filepathObj = fs::weakly_canonical(path);
    exit_if(!fs::exists(_filepathObj), "the file does not exist! %XRs", fs::weakly_canonical(path).c_str());
    _fullPath = fs::weakly_canonical(path);
}

filesInfo Directory::ls() {
    auto directoryIt = fs::directory_iterator(_filepathObj);
    filesInfo infos;
    {
        std::lock_guard<std::mutex> lock(_lsLock);
        for (auto &item : directoryIt) {
            if (item.is_regular_file()) {
                fileInfo info;
                info.name = item.path().filename();
                info.size = humanReadable(item.file_size());
                info.last_write_time = fileTimeToStr(item.last_write_time());
                infos.push_back(info);
            }
        }
    }

    return infos;
}

bool Directory::getSpecialFileDownInfo(filesDownInfo &data, const std::string &name, std::string &errMsg) {
    fileDownInfo info = {};
    if (!getFileDownInfo(info, name, errMsg)) {
        return false;
    }
    data.push_back(info);
    return true;
}

bool Directory::getAllFileDownInfo(filesDownInfo &data, std::string &errMsg) {
    auto directory = fs::directory_iterator{_filepathObj};
    for (auto &it : directory) {
        fileDownInfo info = {};
        std::string errMsg;
        if (getFileDownInfo(info, it.path().filename(), errMsg)) {
            data.push_back(info);
        }
    }
    if (data.empty()) {
        errMsg = "not file exist in the server";
        return false;
    }
    return true;
}

bool Directory::getFileDownInfo(fileDownInfo &data, const std::string &name, std::string &errMsg) {
    auto file = _filepathObj / name;
    std::stringstream errStrStream;
    if (!fs::exists(file)) {
        errStrStream << "file [" << name << "] not exist";
        errMsg = errStrStream.str();
        return false;
    }
    if (!fs::is_regular_file(file)) {
        errStrStream << "file [" << name << "] not be sppurted";
        errMsg = errStrStream.str();
        return false;
    }
    data.name = name;
    data.size = fs::file_size(file);
    data.hash = FileHash::getInstance().getHashByFsPath(file);
    data.humanReadableSize = humanReadable(fs::file_size(file));

    return true;
}

std::string Directory::humanReadable(std::uintmax_t size) {
    std::string res;
    res.resize(10, 0);
    double mantissa = size;
    int i{};
    for (; mantissa >= 1024.0; mantissa /= 1024.0, ++i) {  // 判断mantissa是否有单位默认单位是B，每个单位相差1024
    }
    std::sprintf(&res[0], "%.2f", std::ceil(mantissa * 10.0) / 10.0);
    res += i["BKMGTPE"];
    if (i > 0) {
        res += 'B';
    }
    return res;
}

std::string Directory::fileTimeToStr(std::filesystem::file_time_type time) {
    auto ftimepoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    auto cftime = std::chrono::system_clock::to_time_t(ftimepoint);
    std::string str = std::asctime(std::localtime(&cftime));
    str.pop_back();  // rm the trailing '\n' put by `asctime`
    return str;
}