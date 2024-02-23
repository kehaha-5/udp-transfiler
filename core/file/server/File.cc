#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <filesystem>
#include <string>

#include "Constant.h"
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
    _fileSize = fs::file_size(_filepathObj);
}

bool File::getPosContext(u_long pos, uint size, fileData &data) {
    if (_fileSize > LARGE_FILE_SIZE) {
        return getLargeFilePosContext(pos, size, data);
    }
    return getMinFilePosContext(pos, size, data);
}

bool File::getMinFilePosContext(u_long pos, uint size, fileData &data) {
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

bool File::getLargeFilePosContext(u_long pos, uint size, fileData &data) {
    if (size == 0) {
        setErrMsg(errCode::invalidSzie);
        return false;
    }
    int filefd = open(_filepathObj.c_str(), O_RDONLY);
    if (filefd == -1) {
        setErrMsg(errCode::fileCanNotBeOpened);
        return false;
    }
    struct stat filesb;

    if (fstat(filefd, &filesb) == -1) {
        setErrMsg(errCode::getfileStatError);
        return false;
    }

    uint readLenght;

    if (pos > filesb.st_size) {
        debug_log("pos is %lu filesb.st_size is %lu", pos, filesb.st_size);
        setErrMsg(errCode::fileSzieOut);
        return false;
    }

    if ((pos + size) > filesb.st_size) {
        readLenght = filesb.st_size - pos;
    } else {
        readLenght = size;
    }

    /* offset for mmap() must be page aligned */
    /* https://www.man7.org/linux/man-pages/man2/mmap.2.html offset must be a multiple of the page size as returned by
     * sysconf(_SC_PAGE_SIZE).*/
    std::uintmax_t pa_offset = pos & ~(sysconf(_SC_PAGE_SIZE) - 1);
    std::uintmax_t realReadLenght = readLenght + pos - pa_offset;

    auto addr = mmap(NULL, realReadLenght, PROT_READ, MAP_PRIVATE, filefd, pa_offset);

    if (addr == MAP_FAILED) {
        setErrMsg(errCode::failureInRead);
        warn_log("mmap error %s", strerror(errno));
        return false;
    }

    data.data.resize(readLenght, '\0');

    std::memcpy(&data.data[0], static_cast<char *>(addr) + (pos - pa_offset), readLenght);
    data.realSize = readLenght;

    munmap(addr, readLenght + pos - pa_offset);
    close(filefd);

    return true;
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
        case file::server::errCode::getfileStatError:
            return "get file stat error";
        default:
            return "unkonw error";
    }
}