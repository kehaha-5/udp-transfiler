#include <cassert>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <ios>
#include <mutex>
#include <sstream>
#include <string_view>
#include "utils.h"

#include "FileHash.h"

FileHash& FileHash::getInstance() {
    static FileHash self;
    return self;
}

std::string_view FileHash::getHashByFsPath(const fs::path& path) {
    std::lock_guard<std::mutex> lock_guard(_hashLock);
    auto it = _pathToHash.find(path);
    if (it != _pathToHash.end()) {
        return it->second;
    }
    std::stringstream strStream;
    strStream << std::hex << std::setw(16) << std::hash<fs::path>{}(path);
    _pathToHash.insert({path, utils::trim(strStream.str())});
    it = _pathToHash.find(path);
    assert(it != _pathToHash.end());
    return it->second;
}