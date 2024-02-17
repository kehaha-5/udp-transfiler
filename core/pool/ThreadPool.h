#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <unistd.h>

#include <atomic>
#include <functional>
#include <memory>
#include <queue>
#include <thread>
#include <vector>

#include "EventLoop.h"
namespace pool {
struct QueueItem;
typedef std::vector<std::thread> Threads;
typedef std::unordered_map<int, QueueItem> Queues;
typedef std::unique_ptr<EventLoop> EventLoopPtr;
typedef std::function<void()> queueMsgCb;
typedef std::queue<queueMsgCb> Queue;

struct QueueItem {
    int evenfd = 0;
    Queue queue = {};
    std::mutex mutex;  // Mutex for this Queue
};

class ThreadPool {
   public:
    ThreadPool(int threadNum);
    void sendMsg(queueMsgCb cb);

   private:
    void queueHandle(int index);
    void threadRun(int index);
    Threads _threadPool;
    std::atomic_uint _currThread = 0;
    int _threadNum;
    Queues _msgQueues;
};
}  // namespace pool

#endif
