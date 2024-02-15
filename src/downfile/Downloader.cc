#include <sys/types.h>

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <ios>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

#include "Constant.h"
#include "Downloader.h"
#include "Logging.h"
#include "config/ClientConfig.h"
#include "downfile/DownloaderEvents.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
#include "file/client/File.h"
#include "utils.h"

using namespace downfile;

Downloader::Downloader(file::server::filesDownInfo info, int threadNum, EventPtr even, UdpClientPtr client, AckSetPtr ackSetPtr)
    : _info(info), _even(even), _client(client), _threadNum(threadNum) {
    initDownloadInfo();
    _downloaderEventsPtr = std::make_shared<DownloaderEvents>(_even, _client, _writeMapPtr, _threadNum,ackSetPtr);
}

void Downloader::start() {
    auto downMainThread = std::thread(std::bind([this]() {
        _start = std::chrono::system_clock::now();
        // 发送数据和接收数据并把数据处理分发到线程池
        for (auto &it : _info) {
            auto queue = buildDownQueueByInterruptionData(it.hash);
            _totalSendPackages += queue.size();
            _downloaderEventsPtr->start(queue, it.size);
        }
        _isfinish = true;
        _end = std::chrono::system_clock::now();
    }));
    downMainThread.detach();
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
    // u_long filePackges = std::ceil(info.size / MAX_FILE_DATA_SIZE);
    DownfileInterruptionInfo interruptionData;
    int size = 0;
    for (u_long i = 0; i < info.size; i += MAX_FILE_DATA_SIZE) {
        auto data = interruptionData.add_info();
        data->set_isdownload(false);
        data->set_startpos(size * MAX_FILE_DATA_SIZE);
        size++;
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

std::string Downloader::getDownloadStrDetails(bool getSpeed) {
    std::string details;
    auto data = _downloaderEventsPtr->getDownloadDetail(getSpeed);
    if (_lastDetailsFilename.empty()) {
        _lastDetailsFilename = data.filename;
    }
    if (std::strcmp(_lastDetailsFilename.c_str(), data.filename.c_str()) != 0) {
        details += '\n';
        _lastDetailsFilename = data.filename;
    } else {
        // Move the cursor to the beginning of the current line
        details += '\r';
    }
    details.append(data.filename);
    details.append("  ");

    for (int i = 0; i < 20; i++) {
        if (i < (data.percentage * 2)) {
            details.append("#");
        } else {
            details.append(".");
        }
    }
    details.append("  ");
    details.append(std::to_string(data.percentage * 10) + "%");
    details.append(" ");
    details.append("[hasDown:" + std::to_string(data.hasDownlaodSzie) + "/totalSzie:" + std::to_string(data.totalSize) + "]");
    details.append(" ");
    details.append("[hasRecv:" + std::to_string(data.hasRecvPackages) + "/totalSend:" + std::to_string(data.totalSendPackage) + "]");
    details.append(" ");
    details.append(data.speed);
    details.append("      ");
    return details;
}

std::string Downloader::getDownloadStatistics() {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);
    std::stringstream details;
    details << "\n";
    details << "total download file " << _info.size() << "\n";
    details << "total download size " << utils::humanReadable(_totalSendPackages * MAX_FILE_DATA_SIZE) << "\n";
    details << "total package should be sent " << _totalSendPackages << "\n";
    details << "time-consuming " << duration.count() / 1000 << " s\n";
    details << "speeds " << utils::humanReadable(std::ceil((_totalSendPackages * MAX_FILE_DATA_SIZE) / (duration.count() / 1000)))
            << " peer second \n";
    details << "download finsih \n";
    return details.str();
}

std::string Downloader::getInterruptionFileName(const std::string &fileHash) {
    auto interruptionFilename = "." + fileHash + INTERRUPTION_FILE_SUFFIX;
    return interruptionFilename;
}