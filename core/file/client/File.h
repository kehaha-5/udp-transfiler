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
    bool write(u_long pos, const std::string& data, int size);
    ~File() {
        _file.flush();
        _file.close();
    }
    bool flush();
    std::string& getErrorMsg() { return _errMsg; }

   private:
    fs::path _fileName;
    fs::path _fileDownloadingName;
    std::string _errMsg;
    std::fstream _file;
    std::mutex _fileLock;
    u_long _fileSize;
};
}  // namespace file::client
#endif