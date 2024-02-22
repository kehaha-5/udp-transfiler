#include <bits/ranges_base.h>
#include <sys/types.h>

#include <cmath>
#include <cstring>
#include <iomanip>
#include <memory>
#include <sstream>

#include "Constant.h"
#include "DownloaderStatistics.h"
#include "utils.h"

using namespace downfile;

void DownloaderStatistics::addDetails(std::string filename, bool isDownloaded, interruption::DownfileInterruptionInfo &downloadQueue) {
    DownloadDetailsPtr details = std::make_shared<downloadDetails>();
    details->filename = filename;
    details->isDownloaded = isDownloaded;
    details->totalPackets = static_cast<u_long>(downloadQueue.info_size());
    details->totalSize = downloadQueue.totalsize();
    if (isDownloaded) {
        details->hasDownlaodSize = downloadQueue.hasdownloadedsize();
        for (auto &it : downloadQueue.info()) {
            if (it.isdownload()) {
                details->hasRecvPackets++;
                details->totalSendPackets++;
            }
        }
    }
    _downloaderDetails.insert({filename, details});
}

void DownloaderStatistics::fetchDownloadSize(const u_long &msgSize) { _downloaderDetails[_currFilename]->hasDownlaodSize += msgSize; }

void DownloaderStatistics::fetchHasRecvPackets() { _downloaderDetails[_currFilename]->hasRecvPackets++; }

void DownloaderStatistics::fetchHasResendPackets() { _downloaderDetails[_currFilename]->hasResendPackets++; }

void DownloaderStatistics::fetchTotalSendPackets() { _downloaderDetails[_currFilename]->totalSendPackets++; }

void DownloaderStatistics::fetchSuccessfullyNum() { _successfullyDownloadfileNum++; }

bool DownloaderStatistics::currTaskHasDownloadFinish() {
    return _downloaderDetails[_currFilename]->hasDownlaodSize >= _downloaderDetails[_currFilename]->totalSize;
}

std::string DownloaderStatistics::getDownloadStrStatistics() {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);
    std::stringstream details;
    auto downloaderErrorNum = 0;
    std::stringstream downloadErrorMsg;
    for (auto &it : _downloaderDetails) {
        if (it.second->iserr) {
            downloadErrorMsg << "\t#" << (downloaderErrorNum + 1) << " download error file name " << it.second->filename
                             << " error msg is:" << it.second->errMsg << "\n";
            downloaderErrorNum++;
        }
    }

    details << "\n";
    details << "DOWNLOAD STATISTICS:\n";
    details << "  total download file " << _totalDownloadfileNum << "\n";
    details << "  download successfully file " << _successfullyDownloadfileNum << "\n";
    details << "  download error file " << downloaderErrorNum << "\n";
    details << downloadErrorMsg.str();

    u_long totalSendPackets = 0;
    u_long resnedPackets = 0;
    for (auto &it : _downloaderDetails) {
        totalSendPackets += it.second->totalSendPackets;
        resnedPackets += it.second->hasResendPackets + it.second->totalSendPackets;
    }

    if (totalSendPackets != 0) {
        details << "  total download size " << utils::humanReadable(totalSendPackets * MAX_FILE_DATA_SIZE) << "\n";
        details << "  total packets should be send:" << totalSendPackets << " real packets send:" << (resnedPackets + totalSendPackets)
                << " all resnedPackets:" << resnedPackets << "\n";
        details << "  time-consum "  << std::fixed << std::setprecision(2) << static_cast<double>(duration.count()) / 1000 << " s\n";
        details << "  speeds " << utils::humanReadable(std::ceil((totalSendPackets * MAX_FILE_DATA_SIZE) / (duration.count() / 1000)))
                << " peer second \n";
    }
    details << "  download finsih \n";
    return details.str();
}

std::string DownloaderStatistics::getDownloadDetailStr(bool getSpeed) {
    {
        std::lock_guard<std::mutex> lock_guard(_detailsLock);
        if (_currFilename.empty()) {
            return "\r";
        }
        if (_downloaderDetails[_currFilename]->hasDownlaodSize != 0) {
            _downloaderDetails[_currFilename]->percentage =
                std::round(((_downloaderDetails[_currFilename]->hasDownlaodSize * 100 / _downloaderDetails[_currFilename]->totalSize)));
        }
        if (_downloaderDetails[_currFilename]->totalPackets == _downloaderDetails[_currFilename]->hasRecvPackets) {
            _downloaderDetails[_currFilename]->percentage = 100;
        }
        if (getSpeed) {
            _downloaderDetails[_currFilename]->speed =
                utils::humanReadable((_downloaderDetails[_currFilename]->hasDownlaodSize - _lastDownloadSize));
            _lastDownloadSize = _downloaderDetails[_currFilename]->hasDownlaodSize;
        }
    }

    std::stringstream details;
    if (std::strcmp(_currFilename.c_str(), _currDetailsFilename.c_str()) == 0) {
        // Move the cursor to the beginning of the current line
        details << '\r';
    } else {
        _currDetailsFilename = _currFilename;
        details << '\n';
    }
    auto data = _downloaderDetails[_currFilename];
    // if (data->isDownloaded) {
    //     details << "file has downloaded but not finish , restart download from breakpoint \n";
    // }

    details << (data->filename) << "  ";

    for (int i = 0; i < 20; i++) {
        if (i < ((data->percentage / 10) * 2)) {
            details << "#";
        } else {
            details << ".";
        }
    }
    details << " " << std::to_string(data->percentage) << "%";
    details << " "
            << "size:[down:" << std::to_string(data->hasDownlaodSize) << "/total:" << std::to_string(data->totalSize) << "]";
    details << " "
            << "packets:[total:" << data->totalPackets << "/send:" << std::to_string(data->totalSendPackets)
            << "/recv:" << std::to_string(data->hasRecvPackets) << "/resend:" << std::to_string(data->hasResendPackets)
            << "/ackSet:" << _ackSetPrt->getAckSetSzie() << "]";
    details << " " << data->speed;
    if (data->iserr) {
        details << " err:" << data->errMsg;
    }
    details << "      ";

    return details.str();
}
