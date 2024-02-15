#ifndef SRC_DOWNFILE_DOWNLOADEREVENTS_H
#define SRC_DOWNFILE_DOWNLOADEREVENTS_H

#include <sys/types.h>

#include <atomic>
#include <memory>
#include <queue>

#include "EventLoop.h"
#include "ack/AckSet.h"
#include "file/client/File.h"
#include "msg/proto/file_down_msg.pb.h"
#include "pool/ThreadPool.h"
#include "udp/UdpClient.h"

namespace downfile {

struct downInfo {
    std::string name;
    u_long startPos;
};

struct downloadDetails {
    std::string filename;
    int percentage;  //[0~10]
    std::string speed;
};

typedef std::unique_ptr<pool::ThreadPool> ThreadPoolPtr;
typedef std::shared_ptr<udp::UdpClient> UdpClientPtr;
typedef std::shared_ptr<EventLoop> EventPtr;
typedef std::shared_ptr<file::client::File> ClientFilePtr;
typedef std::shared_ptr<ack::AckSet> AckSetPtr;
typedef std::shared_ptr<std::unordered_map<std::string, ClientFilePtr>> WriteMapPtr;
typedef std::queue<downInfo> DownQueue;

class DownloaderEvents {
   public:
    DownloaderEvents(EventPtr even, UdpClientPtr client, WriteMapPtr writeMapPtr, int threadNum);
    void start(DownQueue& queue, u_long size);
    downloadDetails& getDownloadDetail(bool getSpeed);

   private:
    void setRunning(bool running) { _even->setRunning(running); };
    void sendMsg(msg::proto::FileDownMsg& msg);
    void handlerRecv();
    void loop();
    void initDownloadDetails(std::string filename);
    int _threadNum;
    UdpClientPtr _client;
    EventPtr _even;
    WriteMapPtr _writeMapPtr;
    AckSetPtr _ackSetPtr;
    ThreadPoolPtr _threadPool;
    std::atomic_uint _onceLoop = 0;
    downloadDetails _downloadDetails;
    std::atomic_ulong _hasDownlaodSzie;
    u_long _lastDownloadSzie;
    std::chrono::system_clock::time_point _lastStatisticsTime;
    u_long _totalSzie;
};
}  // namespace downfile
#endif