#ifndef CORE_FILE_SERVER_FILEMAP_h
#define CORE_FILE_SERVER_FILEMAP_h

#include <memory>
#include <mutex>
#include <unordered_map>

#include "file/server/File.h"

namespace file::server {
typedef std::shared_ptr<File> FilePtr;
typedef std::unordered_map<std::string, FilePtr> FilehashToFile;

class FileMap {
   public:
    static FileMap& getInstance();
    bool getFileByFileHash(const std::string& filehash, FilePtr& _filePtr, std::string& errMsg);
    FileMap(const FileMap &) = delete;

   private:
    FileMap(){};
    FilehashToFile _filehashToFile;
    std::mutex _fileMapLock;
};
}  // namespace file::server

#endif