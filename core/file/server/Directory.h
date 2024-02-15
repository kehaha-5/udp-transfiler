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
struct fileDownInfo {
    std::string name;
    u_long size;
    std::string hash;
    std::string humanReadableSize;
};

typedef std::vector<fileDownInfo> filesDownInfo;
class Directory {
   public:
    static Directory &getInstance();
    filesInfo ls();
    std::string getFullPath() { return _fullPath; }
    void setFilePath();
    bool getSpecialFileDownInfo(filesDownInfo &data, const std::string &name, std::string &errMsg);
    bool getAllFileDownInfo(filesDownInfo &data, std::string &errMsg);
    // Delete the copy constructor
    Directory(const Directory &) = delete;

   private:
    bool getFileDownInfo(fileDownInfo &data, const std::string &name, std::string &errMsg);
    std::string fileTimeToStr(std::filesystem::file_time_type time);
    Directory(){};
    fs::path _filepathObj;
    std::string _fullPath;
    std::mutex _lsLock;
};

}  // namespace file::server

#endif