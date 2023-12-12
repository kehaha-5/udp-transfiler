#ifndef FILE_DIRECTORY_H
#define FILE_DIRECTORY_H

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace file {
typedef std::pair<std::string, std::uintmax_t> fileInfo;
typedef std::vector<fileInfo> filesInfo;

class Directory {
   public:
    static Directory* getInstance(std::string path);
    static Directory* getInstance();
    ~Directory() { delete _self; }
    filesInfo ls();

   private:
    Directory(std::string path);
    fs::path _filepathObj;
    static Directory* _self;
};

}  // namespace file

#endif