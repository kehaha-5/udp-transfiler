#include <cassert>
#include <charconv>
#include <cstdio>
#include <filesystem>
#include <memory>

#include "Directory.h"
#include "Logging.h"

using namespace file;

Directory* Directory::_self = nullptr;

Directory* Directory::getInstance(std::string path) {
    if (_self) {
        return _self;
    }
    _self = new Directory(path);
    return _self;
}

Directory* Directory::getInstance() {
    assert(_self != nullptr);
    return _self;
}

Directory::Directory(std::string path) {
    _filepathObj = fs::weakly_canonical(path);
    info_log("the file path is %s", _filepathObj.c_str());
    exit_if(!fs::exists(_filepathObj), "the file does not exist!");
};

filesInfo Directory::ls() {
    auto directoryIt = fs::directory_iterator(_filepathObj);
    filesInfo res;
    for (auto item : directoryIt) {
        if (item.is_regular_file()) {
            res.push_back({item.path().filename(), item.file_size()});
        }
    }
    return res;
}