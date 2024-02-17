#ifndef SRC_DOWNFILE_DOWNLOADER_H
#define SRC_DOWNFILE_DOWNLOADER_H
#include <rapidjson/rapidjson.h>
#include <sys/types.h>

#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "downfile/DownloaderEvents.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
#include "file/client/File.h"
#include "file/server/Directory.h"
#include "udp/UdpClient.h"

namespace downfile {

using namespace interruption;

struct downloaderErrorInfo {
    std::string filename;
    std::string errMsg;
};

typedef std::shared_ptr<udp::UdpClient> UdpClientPtr;
typedef std::shared_ptr<EventLoop> EventPtr;
typedef std::unordered_map<std::string, DownfileInterruptionInfo> DownfileInterruptionInfos;
typedef std::shared_ptr<file::client::File> ClientFilePtr;
typedef std::unordered_map<std::string, ClientFilePtr> WriteMap;
typedef std::shared_ptr<WriteMap> WriteMapPtr;
typedef std::shared_ptr<DownloaderEvents> DownloaderEventsPtr;
typedef std::shared_ptr<ack::AckSet> AckSetPtr;
typedef std::vector<downloaderErrorInfo> DownloaderErrorInfos;

class Downloader {
   public:
    Downloader(file::server::filesDownInfo info, int threadNum, EventPtr even, UdpClientPtr client, AckSetPtr ackSetPtr);
    void start();
    bool hasFinish() { return _isfinish; }
    std::string getDownloadStrDetails(bool getSpeed);
    std::string getDownloadStatistics();
    std::string getErrMsg();

   private:
    void initDownloadInfo();
    void buildInterruptionInfoFile(const file::server::fileDownInfo &info);
    std::string getInterruptionFileName(const std::string &fileHash);
    void flushInterruptionData(std::string &fileHash);
    DownQueue buildDownQueueByInterruptionData(std::string &fileHash);

    DownfileInterruptionInfos _downfileInterruptionInfos;
    UdpClientPtr _client;
    EventPtr _even;
    file::server::filesDownInfo _info;
    WriteMapPtr _writeMapPtr;
    DownloaderEventsPtr _downloaderEventsPtr;
    int _threadNum;
    std::string _lastDetailsFilename;
    std::uintmax_t _totalSendPackages = 0;
    bool _isfinish = false;
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::time_point<std::chrono::system_clock> _end;
    u_long _successfulDownlaodfileNum = 0;
    DownloaderErrorInfos _downloaderErrorInfos;
};
}  // namespace downfile

#endif