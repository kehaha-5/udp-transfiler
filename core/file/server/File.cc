#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include "File.h"
#include "Logging.h"
using namespace file::server;

File::File(std::string path) {
    _filepathObj = path;
    if (!fs::exists(_filepathObj)) {
        setErrMsg(errCode::fileNotExist);
        return;
    }
    if (!fs::is_regular_file(_filepathObj)) {
        setErrMsg(errCode::fileTypeNotSupported);
        return;
    }
}


bool File::getPosContext(int pos, int size, fileData &data) {
    try {
        if (size == 0) {
            setErrMsg(errCode::invalidSzie);
            return false;
        }
        std::ifstream file(_filepathObj, std::ios::binary | std::ios_base::in);
        if (!file.good()) {
            setErrMsg(errCode::fileCanNotBeOpened);
            return false;
        }
        data.data.resize(size, 0);
        file.seekg(pos);
        file.read(&data.data[0], size);
        data.realSize = file.gcount();
        file.close();
        if (data.realSize == 0) {
            setErrMsg(errCode::fileSzieOut);
            return false;
        }
        return true;
    } catch (std::ios_base::failure &e) {
        setErrMsg(errCode::failureInRead);
        warn_log("Caught an ios_base::failure.err msg is %s.err code %i", e.what(), e.code());
        return false;
    }
}


void File::setErrMsg(errCode code) {
    _hasErr = true;
    _err.code = code;
    _err.errMsg = getErrMsgByErrCode(code);
}

std::string File::getErrMsgByErrCode(errCode code) {
    switch (code) {
        case file::server::errCode::fileNotExist:
            return "file not exsit !!!";
        case file::server::errCode::fileTypeNotSupported:
            return "file type not be supported";
        case file::server::errCode::fileCanNotBeOpened:
            return "can not open file";
        case file::server::errCode::failureInRead:
            return "failure in read file";
        case file::server::errCode::fileSzieOut:
            return "file size over limit ";
        case file::server::errCode::invalidSzie:
            return "invail file size";
        default:
            return "unkonw error";
    }
}