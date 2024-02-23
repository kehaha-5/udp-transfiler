#ifndef CORE_FILE_FILE_HASH_H
#define CORE_FILE_FILE_HASH_H

#include <filesystem>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>

namespace file {

namespace fs = std::filesystem;

typedef std::unordered_map<fs::path, std::string> PathToHash;
typedef std::unordered_map<std::string, fs::path> HashToPath;
class FileHash {
   public:
    static FileHash &getInstance();
    std::string_view getHashByFsPath(const fs::path &path);
    fs::path &getFsPathByHash(const std::string filehash);

   private:
    PathToHash _pathToHash;
    HashToPath _hashToPath;
    std::mutex _hashLock;
};
}  // namespace file

#endif