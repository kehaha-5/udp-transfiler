#include <sys/types.h>

#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <memory>
#include <string>

#include "Constant.h"
#include "Downloader.h"
#include "Logging.h"
#include "config/ClientConfig.h"
#include "downfile/DownloaderEvents.h"
#include "downfile/DownloaderStatistics.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
#include "file/client/File.h"

using namespace downfile;

Downloader::Downloader(file::server::filesDownInfo &info, int threadNum, EventPtr &even, UdpClientPtr &client, AckSetPtr &ackSetPtr)
    : _info(info), _even(even), _client(client), _threadNum(threadNum), _ackSetPtr(ackSetPtr) {
    _downloaderStatisticsPtr = std::make_shared<DownloaderStatistics>(ackSetPtr);
    initDownloadInfo();
    _downloaderStatisticsPtr->setDownloadfileNum(info.size() - _filenameIsExist.size());
}

void Downloader::start() {
    _downloaderEventsPtr =
        std::make_shared<DownloaderEvents>(_even, _client, _writeMapPtr, _threadNum, _ackSetPtr, _downloaderStatisticsPtr);
    _downloaderStatisticsPtr->startDownload();
    // 发送数据和接收数据并把数据处理分发到线程池
    for (auto &it : _downfileInterruptionInfos) {
        _downloaderStatisticsPtr->setCurrFilename(it.second.name());
        _downloaderEventsPtr->start(&it.second, it.second.totalsize());
        _downloaderStatisticsPtr->fetchSuccessfullyNum();
    }
    _downloaderStatisticsPtr->endDownload();
    _isfinish = true;
}

void Downloader::initDownloadInfo() {
    WriteMap wp;
    for (const auto &it : _info) {
        auto filename = config::ClientConfig::getInstance().getFilepath() / it.name;
        if (!fs::exists(filename)) {
            auto interruptionFilename = getInterruptionFileName(it.hash);
            bool isDownloaded = false;
            if (fs::exists(interruptionFilename)) {
                std::ifstream file(interruptionFilename, std::ios_base::binary | std::ios_base::in);
                DownfileInterruptionInfo interruptionData;
                if (interruptionData.ParseFromIstream(&file)) {
                    info_log("The file %s has been downloaded, start downloading at breakpoint", it.name.c_str());
                    _downfileInterruptionInfos.insert({it.name, interruptionData});
                    isDownloaded = true;
                    _interruptionWriteMap.insert({it.name, interruptionFilename});
                } else {
                    buildInterruptionInfo(it);
                }
            } else {
                buildInterruptionInfo(it);
            }
            if (_downfileInterruptionInfos.find(it.name) != _downfileInterruptionInfos.end()) {
                _downloaderStatisticsPtr->addDetails(it.name, isDownloaded, _downfileInterruptionInfos.find(it.name)->second);
            }
            // 初始化文件数据
            ClientFilePtr file = std::make_unique<file::client::File>(filename, it.size);
            wp.insert({it.name, file});
        } else {
            _filenameIsExist.push_back(it.name);
        }
    }
    _writeMapPtr = std::make_shared<WriteMap>(wp);
}

void Downloader::buildInterruptionInfo(const file::server::fileDownInfo &info) {
    auto interruptionFilename = getInterruptionFileName(info.hash);
    // u_long filePackges = std::ceil(info.size / MAX_FILE_DATA_SIZE);
    DownfileInterruptionInfo interruptionData;
    int size = 0;
    for (u_long i = 0; i < info.size; i += MAX_FILE_DATA_SIZE) {
        auto data = interruptionData.add_info();
        data->set_isdownload(false);
        data->set_startpos(size * MAX_FILE_DATA_SIZE);
        size++;
    }
    interruptionData.set_hasdownloadedsize(0);
    interruptionData.set_totalsize(info.size);
    interruptionData.set_name(info.name);
    interruptionData.set_isfinish(false);
    _downfileInterruptionInfos.insert({info.name, interruptionData});
    _interruptionWriteMap.insert({info.name, interruptionFilename});
}

void Downloader::flushInterruptionData(const std::string &filename) {
    auto it = _downfileInterruptionInfos.find(filename);
    assert(it != _downfileInterruptionInfos.end());
    auto itt = _interruptionWriteMap.find(filename);
    assert(itt != _interruptionWriteMap.end());
    std::ofstream interruptionFile(itt->second, std::ios_base::binary | std::ios_base::out);
    if (!interruptionFile.good()) {
        warn_log("create download interruption file error");
        return;
    }
    it->second.SerializeToOstream(&interruptionFile);
}

void Downloader::delFlushInterruptionFile(const std::string &filename) {
    auto it = _interruptionWriteMap.find(filename);
    assert(it != _interruptionWriteMap.end());
    if (std::filesystem::exists(it->second)) {
        std::filesystem::remove(it->second);
    }
}

void Downloader::flushAllInterruptionData() {
    _isfinish = true;
    _downloaderEventsPtr.reset();
    for (auto &it : _downfileInterruptionInfos) {
        if (!it.second.isfinish()) {
            flushInterruptionData(it.first);
        } else {
            delFlushInterruptionFile(it.first);
        }
    }
}

std::string Downloader::getDownloadStrDetails(bool getSpeed) { return _downloaderStatisticsPtr->getDownloadDetailStr(getSpeed); }

std::string Downloader::getDownloadStatistics() { return _downloaderStatisticsPtr->getDownloadStrStatistics(); }

std::string Downloader::getInterruptionFileName(const std::string &fileHash) {
    auto interruptionFilename = "." + fileHash + INTERRUPTION_FILE_SUFFIX;
    return config::ClientConfig::getInstance().getFilepath() / interruptionFilename;
}