#ifndef SRC_DOWNFILE_DOWNLOADER_H
#define SRC_DOWNFILE_DOWNLOADER_H
#include <rapidjson/rapidjson.h>
#include <sys/types.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "downfile/DownloaderEvents.h"
#include "downfile/DownloaderStatistics.h"
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
typedef std::unordered_map<std::string, DownfileInterruptionInfo> DownfileInterruptionInfos;  //[filename => DownfileInterruptionInfo]
typedef std::shared_ptr<file::client::File> ClientFilePtr;
typedef std::unordered_map<std::string, ClientFilePtr> WriteMap;            //[filename => clientFilePtr]
typedef std::unordered_map<std::string, std::string> InterruptionWriteMap;  // [filename => interruptionfilename]
typedef std::shared_ptr<WriteMap> WriteMapPtr;
typedef std::shared_ptr<DownloaderEvents> DownloaderEventsPtr;
typedef std::shared_ptr<ack::AckSet> AckSetPtr;
typedef std::shared_ptr<DownloaderStatistics> DownloaderStatisticsPtr;
typedef std::vector<std::string> FilenameIsExist;

class Downloader {
   public:
    Downloader(file::server::filesDownInfo &info, int threadNum, EventPtr &even, UdpClientPtr &client, AckSetPtr &ackSetPtr);
    void start();
    bool hasFinish() { return _isfinish; }
    std::string getDownloadStrDetails(bool getSpeed);
    std::string getDownloadStatistics();
    std::string getErrMsg();
    FilenameIsExist &getfilenameExistInfo() { return _filenameIsExist; };
    ~Downloader() {
        flushAllInterruptionData();
    }
    void flushAllInterruptionData();  //在接受到ctrl+c时不一定能够执行构型函数，因此要把该函数暴露出去

   private:
    void initDownloadInfo();
    void buildInterruptionInfo(const file::server::fileDownInfo &info);
    std::string getInterruptionFileName(const std::string &fileHash);
    void flushInterruptionData(const std::string &filename);
    void delFlushInterruptionFile(const std::string &filename);
    void singalHandler(int signal);

    DownfileInterruptionInfos _downfileInterruptionInfos;
    UdpClientPtr _client;
    EventPtr _even;
    file::server::filesDownInfo _info;
    WriteMapPtr _writeMapPtr;
    InterruptionWriteMap _interruptionWriteMap;
    DownloaderEventsPtr _downloaderEventsPtr;
    FilenameIsExist _filenameIsExist;
    int _threadNum;
    std::string _lastDetailsFilename;
    std::uintmax_t _totalSendPackets = 0;
    bool _isfinish = false;
    u_long _successfulDownlaodfileNum = 0;
    DownloaderStatisticsPtr _downloaderStatisticsPtr;
    AckSetPtr _ackSetPtr;
};
}  // namespace downfile

#endif