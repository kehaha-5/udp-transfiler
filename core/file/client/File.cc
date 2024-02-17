#include <sys/types.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>

#include "File.h"

using namespace file::client;

File::File(std::string fileName, u_long size) {
    _fileName = fileName;
    if (fs::exists(_fileName)) {
        if (fs::file_size(_fileName) == size) {
            _init = true;
        } else {
            fs::remove(_fileName);
        }
    }
    _fileSize = size;
    _file.open(_fileName, std::ios_base::binary | std::ios_base::out);
}

bool File::init() {
    if (_init) {
        char buff[SINGLE_WRITE_SIZE] = {0};
        std::memset(buff, 0, SINGLE_WRITE_SIZE);
        auto i = SINGLE_WRITE_SIZE;
        for (; i < _fileSize; i += SINGLE_WRITE_SIZE) {
            _file.write(buff, SINGLE_WRITE_SIZE);
        }
        _file.write(buff, (i += SINGLE_WRITE_SIZE) - _fileSize);
    }
    _init = true;
    return true;
}

bool File::write(int pos, const std::string& data, int size) {
    if (!_file.good()) {
        _errMsg = "file is not good ";
        return false;
    }
    {
        std::lock_guard<std::mutex> lock_guard(_fileLock);
        _file.seekp(pos);
        if (!_file.good()) {
            _errMsg = "file seekp error";
            return false;
        }
        _file.write(data.c_str(), size);
    }
    return true;
}
