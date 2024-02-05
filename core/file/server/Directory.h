#ifndef FILE_DIRECTORY_H
#define FILE_DIRECTORY_H

#include <filesystem>
#include <mutex>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace file::server {

struct fileInfo {
    std::string last_write_time;
    std::string size;
    std::string name;
};

typedef std::vector<fileInfo> filesInfo;

class Directory {
   public:
    static Directory& getInstance(std::string path);
    static Directory& getInstance();
    filesInfo ls();
    std::string getFullPath() { return _fullPath; }
    void setFilePath(std::string path);

   private:
    std::string humanReadable(std::uintmax_t size);
    std::string fileTimeToStr(std::filesystem::file_time_type time);
    Directory(){};
    fs::path _filepathObj;
    std::string _fullPath;
    std::mutex _lsLock;
};

}  // namespace file::server

#endif