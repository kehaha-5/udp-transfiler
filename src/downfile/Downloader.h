#ifndef SRC_DOWNFILE_DOWNLOADER_H
#define SRC_DOWNFILE_DOWNLOADER_H
#include <rapidjson/rapidjson.h>
#include <sys/types.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "Constant.h"
#include "downfile/DownloaderEvents.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
#include "file/client/File.h"
#include "file/server/Directory.h"
#include "udp/UdpClient.h"

namespace downfile {

using namespace interruption;

const int CACHE_REQ_NUM = 10;
const int CACHE_DATA_SIZE = CACHE_REQ_NUM * MAX_FILE_DATA_SIZE;

typedef std::shared_ptr<udp::UdpClient> UdpClientPtr;
typedef std::shared_ptr<EventLoop> EventPtr;
typedef std::unordered_map<std::string, DownfileInterruptionInfo> DownfileInterruptionInfos;
typedef std::shared_ptr<file::client::File> ClientFilePtr;
typedef std::unordered_map<std::string, ClientFilePtr> WriteMap;
typedef std::shared_ptr<WriteMap> WriteMapPtr;
typedef std::shared_ptr<DownloaderEvents> DownloaderEventsPtr;

class Downloader {
   public:
    Downloader(file::server::filesDownInfo info, int threadNum, EventPtr even, UdpClientPtr client);
    void start();
    bool hasFinish() { return _isfinish; }
    std::string getDownloadStrDetails(bool getSpeed);

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
    bool _isfinish = false;
};
}  // namespace downfile

#endif