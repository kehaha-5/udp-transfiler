#ifndef FIEL_FILE_H
#define FIEL_FILE_H

#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace file::server {

enum errCode {
    fileNotExist = 0,
    fileTypeNotSupported,
    fileCanNotBeOpened,
    failureInRead,
    fileSzieOut,
    invalidSzie,
    getfileStatError,
    fileCanNotBeRead
};

struct errMsg {
    errCode code;
    std::string errMsg;
};

struct fileData {
    std::string data;
    int realSize;
};

class File {
   public:
    File(std::string path);
    bool hasError() { return _hasErr; }
    errMsg getErrMsg() { return _err; }
    bool getPosContext(int pos, int size, fileData& data);
    bool getPosContext2(int pos, int size, fileData& data);

   private:
    void setErrMsg(errCode code);
    std::string getErrMsgByErrCode(errCode code);
    bool _hasErr = false;
    errMsg _err;
    fs::path _filepathObj;
    std::ifstream _file;
};
}  // namespace file::server

#endif