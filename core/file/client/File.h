#ifndef CORE_FILE_CLIENT_FILE_H
#define CORE_FILE_CLIENT_FILE_H

#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>

namespace file::client {

const int SINGLE_WRITE_SIZE = 1024;

namespace fs = std::filesystem;
class File {
   public:
    File(std::string fileName, u_long size);
    bool init();
    bool wirite(int pos, const std::string& data, int size);
    ~File() { _file.close(); }

   private:
    fs::path _fileName;
    std::string _errMsg;
    std::ofstream _file;
    std::mutex _fileLock;
    u_long _fileSize;
    bool _init = false;
};
}  // namespace file::client
#endif