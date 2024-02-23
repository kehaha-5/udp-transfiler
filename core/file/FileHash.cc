#include <cassert>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <ios>
#include <mutex>
#include <sstream>
#include <string_view>

#include "FileHash.h"
#include "utils.h"

using namespace file;

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
    _hashToPath.insert({utils::trim(strStream.str()), path});
    assert(it != _pathToHash.end());
    return it->second;
}

fs::path& FileHash::getFsPathByHash(const std::string filehash) {
    std::lock_guard<std::mutex> lock_guard(_hashLock);
    auto it = _hashToPath.find(filehash);
    assert(it != _hashToPath.end());
    return it->second;
}
