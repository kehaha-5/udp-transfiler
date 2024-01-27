#include <sys/types.h>

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <string>

#include "Directory.h"
#include "Logging.h"

using namespace file;

Directory& Directory::getInstance() {
    static Directory _self;
    return _self;
}

void Directory::setFilePath(std::string path) {
    _filepathObj = fs::weakly_canonical(path);
    exit_if(!fs::exists(_filepathObj), "the file does not exist!");
    _fullPath = fs::weakly_canonical(path);
}

filesInfo Directory::ls() {
    auto directoryIt = fs::directory_iterator(_filepathObj);
    filesInfo infos;
    for (auto item : directoryIt) {
        if (item.is_regular_file()) {
            fileInfo info;
            info.name = item.path().filename();
            info.size = humanReadable(item.file_size());
            info.last_write_time = fileTimeToStr(item.last_write_time());
            infos.push_back(info);
        }
    }
    return infos;
}

std::string Directory::humanReadable(std::uintmax_t size) {
    std::string res;
    char* buff = new char[10];  // 整数最多为4位超过4位上升一个单位，小数点一位，小数最多两位，终止\0符号一位
    std::memset(buff, 0, 10);
    double mantissa = size;
    int i{};
    for (; mantissa >= 1024.0; mantissa /= 1024.0, ++i) {  // 判断mantissa是否有单位默认单位是B，每个单位相差1024
    }
    std::sprintf(buff, "%.2f", std::ceil(mantissa * 10.0) / 10.0);
    res = buff;
    res += i["BKMGTPE"];
    if (i > 0) {
        res += 'B';
    }
    delete[] buff;
    return res;
}

std::string Directory::fileTimeToStr(std::filesystem::file_time_type time) {
    auto ftimepoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(time - std::filesystem::file_time_type::clock::now() +
                                                                                        std::chrono::system_clock::now());
    auto cftime = std::chrono::system_clock::to_time_t(ftimepoint);
    std::string str = std::asctime(std::localtime(&cftime));
    str.pop_back();  // rm the trailing '\n' put by `asctime`
    return str;
}