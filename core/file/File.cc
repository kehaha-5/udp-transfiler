#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

#include "Constant.h"
#include "File.h"
#include "Logging.h"

using namespace file;

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
        std::ifstream file(_filepathObj, std::ios::binary);
        if (!file.is_open()) {
            setErrMsg(errCode::fileCanNotBeOpened);
            return false;
        }
        data.data.resize(MAX_FILE_DATA_SIZE, '\0');
        file.seekg(pos);
        file.read(&data.data[0], size);
        data.realSize = file.gcount();
        file.close();
        if (data.realSize == 0) {
            setErrMsg(errCode::fileSzieOut);
            return false;
        }
        data.hash = std::hash<std::string>{}(data.data);
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
        case file::errCode::fileNotExist:
            return "文件不存在";
        case file::errCode::fileTypeNotSupported:
            return "不支持该文件类型的";
        case file::errCode::fileCanNotBeOpened:
            return "文件无法被打开";
        case file::errCode::failureInRead:
            return "文件读取错误";
        case file::errCode::fileSzieOut:
            return "文件szie超出大小";
        case file::errCode::invalidSzie:
            return "非法长度";
        default:
            return "未知错误";
    }
}