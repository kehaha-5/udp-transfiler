#include <sys/types.h>

#include <cassert>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <ios>
#include <memory>
#include <thread>

#include "Constant.h"
#include "Downloader.h"
#include "Logging.h"
#include "config/ClientConfig.h"
#include "downfile/DownloaderEvents.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
#include "file/client/File.h"

using namespace downfile;

Downloader::Downloader(file::server::filesDownInfo info, int threadNum, EventPtr even, UdpClientPtr client)
    : _info(info), _even(even), _client(client), _threadNum(threadNum) {}

void Downloader::start() {
    initDownloadInfo();
    _downloaderEventsPtr = std::make_shared<DownloaderEvents>(_even, _client, _writeMapPtr, _threadNum);
    auto downloadThread = std::thread(std::bind([this]() {
        // 发送数据和接收数据并把数据处理分发到线程池
        for (auto &it : _info) {
            auto queue = buildDownQueueByInterruptionData(it.hash);
            _downloaderEventsPtr->start(queue);
        }
        _isfinish = true;
    }));
    downloadThread.detach();
}

void Downloader::initDownloadInfo() {
    WriteMap wp;
    for (const auto &it : _info) {
        auto interruptionFilename = getInterruptionFileName(it.hash);
        if (fs::exists(interruptionFilename)) {
            std::fstream file(interruptionFilename, std::ios_base::binary | std::ios_base::in);
            DownfileInterruptionInfo interruptionData;
            if (interruptionData.ParseFromIstream(&file)) {
                info_log("The file %s has been downloaded, start downloading at breakpoint", it.name.c_str());
                _downfileInterruptionInfos.insert({it.hash, interruptionData});
            } else {
                buildInterruptionInfoFile(it);
            }
        } else {
            buildInterruptionInfoFile(it);
        }
        // 初始化文件数据
        ClientFilePtr file = std::make_unique<file::client::File>(config::ClientConfig::getInstance().getFilepath() / it.name, it.size);
        file->init();
        wp.insert({it.name, file});
    }
    _writeMapPtr = std::make_shared<WriteMap>(wp);
}

void Downloader::buildInterruptionInfoFile(const file::server::fileDownInfo &info) {
    auto interruptionFilename = getInterruptionFileName(info.hash);
    std::ofstream interruptionFile(config::ClientConfig::getInstance().getFilepath() / interruptionFilename,
                                   std::ios_base::binary | std::ios_base::out);
    if (!interruptionFile.good()) {
        warn_log("create download interruption file error");
        return;
    }
    u_long filePackges = std::ceil(info.size / MAX_FILE_DATA_SIZE);
    DownfileInterruptionInfo interruptionData;
    for (u_long i = 0; i < filePackges; i++) {
        auto data = interruptionData.add_info();
        data->set_isdownload(false);
        data->set_startpos(i * MAX_FILE_DATA_SIZE);
    }
    interruptionData.set_hasdownloadedszie(0);
    interruptionData.set_name(info.name);
    if (!interruptionData.SerializeToOstream(&interruptionFile)) {
        warn_log("save data to download interruption file error,file name is %s", interruptionFilename.c_str());
    }
    _downfileInterruptionInfos.insert({info.hash, interruptionData});
}

void Downloader::flushInterruptionData(std::string &fileHash) {
    auto it = _downfileInterruptionInfos.find(fileHash);
    assert(it != _downfileInterruptionInfos.end());
    auto interruptionFilename = getInterruptionFileName(fileHash);
    std::ofstream interruptionFile(interruptionFilename, std::ios_base::binary | std::ios_base::out);
    if (!interruptionFile.good()) {
        warn_log(" download interruption file open error");
        return;
    }
    it->second.SerializeToOstream(&interruptionFile);
}

DownQueue Downloader::buildDownQueueByInterruptionData(std::string &fileHash) {
    auto it = _downfileInterruptionInfos.find(fileHash);
    assert(it != _downfileInterruptionInfos.end());
    DownQueue downQueue;
    for (int i = 0; i < it->second.info_size(); i++) {
        auto data = it->second.info(i);
        if (!data.isdownload()) {
            downInfo msg{it->second.name(), data.startpos()};
            downQueue.push(msg);
        }
    }
    return downQueue;
}

std::string Downloader::getInterruptionFileName(const std::string &fileHash) {
    auto interruptionFilename = "." + fileHash + INTERRUPTION_FILE_SUFFIX;
    return interruptionFilename;
}