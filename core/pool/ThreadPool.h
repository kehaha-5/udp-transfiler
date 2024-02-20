#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <unistd.h>

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include "EventLoop.h"
namespace pool {
struct QueueItem;
typedef std::vector<std::thread> Threads;
typedef std::unordered_map<int, QueueItem> Queues;
typedef std::function<void()> queueMsgCb;
typedef std::queue<queueMsgCb> Queue;
typedef std::shared_ptr<EventLoop> EventLoopPtr;
typedef std::unordered_map<int, EventLoopPtr> EventMap;

struct QueueItem {
    int evenfd = 0;
    Queue queue = {};
    std::mutex mutex;  // Mutex for this Queue
};

class ThreadPool {
   public:
    ThreadPool(int threadNum);
    void sendMsg(queueMsgCb cb);
    void closeThreadPool();

   private:
    void queueHandle(int index);
    void threadRun(int index);
    Threads _threadPool;
    std::atomic_uint _currThread = 0;
    int _threadNum;
    Queues _msgQueues;
    EventMap _eventMap;
    std::mutex _eventMapLock;
};
}  // namespace pool

#endif
