#include <sys/types.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <mutex>

#include "Constant.h"
#include "File.h"

using namespace file::client;

File::File(std::string fileName, u_long size) {
    _fileName = fileName;
    _fileDownloadingName = fileName.append(DOWNLOAD_ING_FILE_SUFFIX);
    if (fs::exists(_fileDownloadingName)) {
        _file.open(_fileDownloadingName, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    } else {
        _file.open(_fileDownloadingName, std::ios_base::binary | std::ios_base::out);
    }
    _fileSize = size;
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

bool File::flush() {
    _file.flush();
    std::error_code errCode;
    fs::rename(_fileDownloadingName, _fileName, errCode);
    _errMsg = errCode.message();
    return true;
}