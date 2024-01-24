#ifndef FILE_DIRECTORY_H
#define FILE_DIRECTORY_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace file {

struct fileInfo {
    std::string last_write_time;
    std::string size;
    std::string name;
};
typedef std::vector<fileInfo> filesInfo;

class Directory {
   public:
    static Directory* getInstance(std::string path);
    static Directory* getInstance();
    ~Directory() { delete _self; }
    filesInfo ls();

   private:
    std::string humanReadable(std::uintmax_t size);
    std::string fileTimeToStr(std::filesystem::file_time_type time);
    Directory(std::string path);
    fs::path _filepathObj;
    static Directory* _self;
};

}  // namespace file

#endif