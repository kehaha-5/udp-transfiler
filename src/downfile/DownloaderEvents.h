#ifndef SRC_DOWNFILE_DOWNLOADEREVENTS_H
#define SRC_DOWNFILE_DOWNLOADEREVENTS_H

#include <sys/types.h>

#include <memory>
#include <mutex>
#include <queue>

#include "EventLoop.h"
#include "ack/AckSet.h"
#include "downfile/DownloaderStatistics.h"
#include "downfile/interruptionInfo/downfile_interruption_info.pb.h"
#include "file/client/File.h"
#include "msg/Msg.h"
#include "msg/proto/file_down_msg.pb.h"
#include "pool/ThreadPool.h"
#include "udp/UdpClient.h"

namespace downfile {

struct sendQueueItem {
    std::string filename;
    u_long startPos;
    u_long index;
};

typedef std::unique_ptr<pool::ThreadPool> ThreadPoolPtr;
typedef std::shared_ptr<udp::UdpClient> UdpClientPtr;
typedef std::shared_ptr<EventLoop> EventPtr;
typedef std::shared_ptr<file::client::File> ClientFilePtr;
typedef std::shared_ptr<ack::AckSet> AckSetPtr;
typedef std::shared_ptr<std::unordered_map<std::string, ClientFilePtr>> WriteMapPtr;
typedef std::queue<sendQueueItem> SendDataQueue;
typedef std::shared_ptr<DownloaderStatistics> DownloaderStatisticsPtr;

class DownloaderEvents {
   public:
    DownloaderEvents(EventPtr& even, UdpClientPtr& client, WriteMapPtr& writeMapPtr, int threadNum, AckSetPtr& ackSetPtr,
                     DownloaderStatisticsPtr& dfstatisticsPtr);
    void start(interruption::DownfileInterruptionInfo* downloadQueue, u_long size);
    ~DownloaderEvents() {
        _threadPool->closeThreadPool();
        _recvEvent->setRunning(false);
    }

   private:
    std::string& getErrMsg() { return _errMsg; };
    bool sendMsg(msg::proto::FileDownMsg& msg);
    void handlerRecv();
    void listenResq();
    void sendRes();
    void initDownloadDetails(std::string filename);
    void timerExce(u_long ack, std::vector<msg::Package> msg);
    void setErrMsg(std::string errMsg);
    void setDataWithEvents();  // in the non-blocking udp socket sendto mabe EAGAIN or EWOULDBLOCK
    int _threadNum;
    UdpClientPtr _client;
    EventPtr _recvEvent;
    EventPtr _sendEvent;
    WriteMapPtr _writeMapPtr;
    AckSetPtr _ackSetPtr;
    ThreadPoolPtr _threadPool;
    DownloaderStatisticsPtr _downloaderStatisticsPtr;
    std::mutex _detailsLock;
    std::mutex _recvLock;
    std::mutex _seterrLock;
    std::mutex _updateInterruptionDataLock;
    bool _err = false;
    std::string _errMsg;
    interruption::DownfileInterruptionInfo* _currInterruptionData;
    SendDataQueue _sendDataQueue;
};
}  // namespace downfile
#endif