#ifndef SRC_DOWNFILE_DONWNLOADERSTATISTICS_H
#define SRC_DOWNFILE_DONWNLOADERSTATISTICS_H

#include <sys/types.h>

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "ack/AckSet.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
namespace downfile {

struct downloadDetails {
    std::string filename;  //文件名称
    bool isDownloaded;
    int percentage = 0;                      //[0~100]
    std::string speed = "-/-";               //下载速度
    u_long totalSize = 0;                    //下载总大小
    std::atomic_ulong hasDownlaodSize = 0;   //已经下载大小
    u_long totalPackets;                     //总包数量
    std::atomic_ulong hasRecvPackets = 0;    //已经接受数据包大小
    std::atomic_ulong totalSendPackets = 0;  //所有发送的数据包数量
    std::atomic_ulong hasResendPackets = 0;  //所有重发的数据包数量
    bool iserr = false;
    std::string errMsg;
};

typedef std::shared_ptr<downloadDetails> DownloadDetailsPtr;
typedef std::unordered_map<std::string, DownloadDetailsPtr> DownloaderDetails;  //[filename => DownloadDetailsPtr]
typedef std::shared_ptr<ack::AckSet> AckSetPtr;

class DownloaderStatistics {
   public:
    DownloaderStatistics(AckSetPtr &ackSetPrt) : _ackSetPrt(ackSetPrt) {}
    void addDetails(std::string filename, bool isDownloaded, interruption::DownfileInterruptionInfo &downloadQueue);
    void fetchTotalSize(u_long &size);
    void fetchDownloadSize(const u_long &msgSize);
    void fetchHasRecvPackets();
    void fetchTotalSendPackets();
    void fetchHasResendPackets();
    void fetchSuccessfullyNum();
    void startDownload() { _start = std::chrono::system_clock::now(); };
    void endDownload() { _end = std::chrono::system_clock::now(); };
    bool currTaskHasDownloadFinish();
    void setDownloadfileNum(u_long totalDownloadfileNum) { _totalDownloadfileNum = totalDownloadfileNum; };
    void setCurrFilename(const std::string &filename) {
        std::lock_guard<std::mutex> lock_guard(_detailsLock);
        _currFilename = filename;
        _lastDownloadSize = 0;
    };
    void setDownloadError(std::string &errmsg) {
        _downloaderDetails[_currFilename]->iserr = true;
        _downloaderDetails[_currFilename]->errMsg = errmsg;
    };
    std::string getDownloadDetailStr(bool getSpeed);
    std::string getDownloadStrStatistics();

   private:
    std::string _currFilename;
    u_long _totalDownloadfileNum = 0;
    std::string _currDetailsFilename;
    DownloaderDetails _downloaderDetails = {};
    u_long _lastDownloadSize = 0;
    std::mutex _detailsLock;
    u_long _successfullyDownloadfileNum = 0;
    AckSetPtr _ackSetPrt;
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::time_point<std::chrono::system_clock> _end;
};
}  // namespace downfile

#endif