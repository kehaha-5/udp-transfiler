#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include "FileMap.h"
#include "config/ServerConfig.h"
#include "file/FileHash.h"
#include "file/server/File.h"

using namespace file::server;

FileMap& FileMap::getInstance() {
    static FileMap ins;
    return ins;
}

bool FileMap::getFileByFileHash(const std::string& filehash, FilePtr& _filePtr, std::string& errMsg) {
    std::lock_guard<std::mutex> lock_gurad(_fileMapLock);
    auto it = _filehashToFile.find(filehash);
    if (it == _filehashToFile.end()) {
        auto filePtr =
            std::make_shared<File>(config::ServerConfig::getInstance().getFilepath() / FileHash::getInstance().getFsPathByHash(filehash));
        if (filePtr->hasError()) {
            errMsg = filePtr->getErrMsg().errMsg;
            return false;
        }
        _filehashToFile.emplace(std::make_pair(filehash, filePtr));
        _filePtr = filePtr;
        return true;
    }
    _filePtr = it->second;
    return true;
}