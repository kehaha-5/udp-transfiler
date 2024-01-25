#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <unistd.h>

#include <atomic>
#include <cassert>
#include <functional>
#include <memory>
#include <queue>
#include <thread>
#include <utility>
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
    int evenfd;
    Queue queue;
};

class ThreadPool {
   public:
    ThreadPool(int threadNum);
    void sendMsg(queueMsgCb cb);
    ~ThreadPool() {
        for (auto it = _msgQueues.begin(); it != _msgQueues.end(); it++) {
            QueueItem queueItem = it->second;
            close(queueItem.evenfd);
            assert(queueItem.queue.size() == 0);
        }
        _msgQueues.clear();
        _threadPool.clear();
        _threadPool.shrink_to_fit();
    };

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
