#include <sys/eventfd.h>

#include <cassert>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

#include "Logging.h"
#include "pool/ThreadPool.h"
using namespace pool;

void ThreadPool::queueHandle(int index) {
    auto queueItemIt = _msgQueues.find(index);
    while (!queueItemIt->second.queue.empty()) {
        unsigned long long number;
        read(queueItemIt->second.evenfd, &number, sizeof(unsigned long long));
        queueMsgCb cd = queueItemIt->second.queue.front();
        cd();
        {
            std::lock_guard<std::mutex> lock_guard(queueItemIt->second.mutex);
            queueItemIt->second.queue.pop();
        }
    }
};

void ThreadPool::threadRun(int index) {
    EventLoopPtr loop = std::make_shared<EventLoop>();
    _eventMap.insert({_msgQueues[index].evenfd, loop});
    loop->addIo(_msgQueues[index].evenfd, std::bind(&ThreadPool::queueHandle, this, index), EPOLLIN);
    loop->loop();
}

ThreadPool::ThreadPool(int threadNum) {
    _threadNum = threadNum;
    for (int i = 0; i < threadNum; i++) {
        int evenfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
        _msgQueues[i].evenfd = evenfd;
        _msgQueues[i].queue = {};
        // _msgQueues.emplace(i, QueueItem{evenfd, {}});

        _threadPool.push_back(std::thread(std::bind(&ThreadPool::threadRun, this, i)));
    }
    for (int i = 0; i < threadNum; i++) {
        _threadPool[i].detach();
    }
}

void ThreadPool::sendMsg(queueMsgCb cb) {
    // QueueItem queueItem = _msgQueues[_currThread]; err get the rvalue
    auto queueItem = _msgQueues.find(_currThread);
    _currThread++;
    if (_currThread == _threadNum) {
        _currThread = 0;
    }
    {
        std::lock_guard<std::mutex> lock_guard(queueItem->second.mutex);
        queueItem->second.queue.push(cb);
    }
    unsigned long long number = 1;
    /* https://man7.org/linux/man-pages/man2/eventfd.2.html
       A write(2) fails with the error EINVAL if the size of the
       supplied buffer is less than 8 bytes, or if an attempt is
       made to write the value 0xffffffffffffffff.
    */
    int len = write(queueItem->second.evenfd, &number, sizeof(unsigned long long));

    exit_if(len == -1, "add task to queue error");
}

void ThreadPool::closeThreadPool() {
    for (auto &it : _msgQueues) {
        {
            std::lock_guard<std::mutex> lock_guard(it.second.mutex);
            while (!it.second.queue.empty()) {
            };
            auto itt = _eventMap.find(it.second.evenfd);
            itt->second->setRunning(false);
        }
    }
}