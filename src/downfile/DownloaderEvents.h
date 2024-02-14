#ifndef SRC_DOWNFILE_DOWNLOADEREVENTS_H
#define SRC_DOWNFILE_DOWNLOADEREVENTS_H

#include <memory>
#include <queue>

#include "EventLoop.h"
#include "ack/AckSet.h"
#include "file/client/File.h"
#include "msg/Buffer.h"
#include "msg/proto/file_down_msg.pb.h"
#include "pool/ThreadPool.h"
#include "udp/UdpClient.h"

namespace downfile {

struct downInfo {
    std::string name;
    u_long startPos;
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
    void start(DownQueue& queue);

   private:
    void setRunning(bool running) { _even->setRunning(running); };
    void sendMsg(FileDownMsg &msg);
    void handlerRecv();
    void loop();
    int _threadNum;
    UdpClientPtr _client;
    EventPtr _even;
    WriteMapPtr _writeMapPtr;
    AckSetPtr _ackSetPtr;
    ThreadPoolPtr _threadPool;
    std::atomic_uint _onceLoop = 0;
};
}  // namespace downfile
#endif