#ifndef CORE_FILE_FILE_HASH_H
#define CORE_FILE_FILE_HASH_H

#include <filesystem>
#include <mutex>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

typedef std::unordered_map<fs::path, std::string> PathToHash;

class FileHash {
   public:
    static FileHash &getInstance();
    std::string_view getHashByFsPath(const fs::path &path);

   private:
    PathToHash _pathToHash;
    std::mutex _hashLock;
};

#endif