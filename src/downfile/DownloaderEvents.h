#ifndef SRC_DOWNFILE_DOWNLOADEREVENTS_H
#define SRC_DOWNFILE_DOWNLOADEREVENTS_H

#include <sys/types.h>

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>

#include "EventLoop.h"
#include "ack/AckSet.h"
#include "file/client/File.h"
#include "msg/Msg.h"
#include "msg/proto/file_down_msg.pb.h"
#include "pool/ThreadPool.h"
#include "udp/UdpClient.h"

namespace downfile {

struct downInfo {
    std::string name;
    u_long startPos;
};

struct downloadDetails {
    std::string filename;        //文件名称
    int percentage = 0;          //[0~10]
    std::string speed = "-/-";   //下载速度
    u_long totalSize = 0;        //下载总大小
    u_long hasDownlaodSzie = 0;  //已经下载大小
    uint hasRecvPackages = 0;    //已经接受数据包大小
    uint totalSendPackage = 0;   //所有发送的数据包数量
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
    DownloaderEvents(EventPtr even, UdpClientPtr client, WriteMapPtr writeMapPtr, int threadNum, AckSetPtr ackSetPtr);
    void start(DownQueue& queue, u_long size);
    downloadDetails& getDownloadDetail(bool getSpeed);

   private:
    void setRunning(bool running) { _even->setRunning(running); };
    void sendMsg(msg::proto::FileDownMsg& msg);
    void handlerRecv();
    void loop();
    void initDownloadDetails(std::string filename);
    void timerExce(u_long ack, std::vector<msg::Package> msg);
    int _threadNum;
    UdpClientPtr _client;
    EventPtr _even;
    WriteMapPtr _writeMapPtr;
    AckSetPtr _ackSetPtr;
    ThreadPoolPtr _threadPool;
    downloadDetails _downloadDetails;         //当前下载详情
    std::atomic_ulong _hasDownlaodSzie = 1;   //已经下载大小
    std::atomic_uint _hasRecvPackages = 0;    //已经收到包数量
    std::atomic_uint _totalSendPackages = 0;  //总发送包数量
    u_long _lastDownloadSzie;                 //上次下载大小 用于统计速度
    u_long _totalSzie;                        //整个包大小
    std::mutex _detailsLock;
};
}  // namespace downfile
#endif