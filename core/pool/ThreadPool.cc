#include <sys/epoll.h>
#include <sys/eventfd.h>

#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

#include "Logging.h"
#include "pool/ThreadPool.h"
using namespace pool;

void ThreadPool::queueHandle(int index) {
    if (!_isRunning) {
        return;
    }
    auto queueItemIt = _msgQueues.find(index);
    auto eventPtr = _eventMap.find(queueItemIt->second.evenfd);
    while (!queueItemIt->second.queue.empty()) {
        if (!eventPtr->second->isRunning()) {  //线程要关闭了
            return;
        }
        {
            std::lock_guard<std::mutex> lock_guard(queueItemIt->second.mutex);
            queueMsgCb cd = queueItemIt->second.queue.front();
            cd();
            queueItemIt->second.queue.pop();
        }
        unsigned long long number;
        if (read(queueItemIt->second.evenfd, &number, sizeof(unsigned long long)) == -1) {
            if (!(errno == EAGAIN || errno == EWOULDBLOCK)) {
                warn_log("queuehandle read error %s", strerror(errno));
            }
        }
    }
};

void ThreadPool::threadRun(int index) {
    EventLoopPtr loop = std::make_shared<EventLoop>();
    {
        std::lock_guard<std::mutex> lock_guard(_eventMapLock);
        _eventMap.insert({_msgQueues[index].evenfd, loop});
    }
    loop->addIo(_msgQueues[index].evenfd, std::bind(&ThreadPool::queueHandle, this, index), EPOLLIN | EPOLLET);
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
    if (!_isRunning) {
        return;
    }
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

void ThreadPool::closeThreadPool(bool force) {
    if (!_isRunning) {
        return;
    }
    _isRunning = false;
    for (auto &it : _msgQueues) {
        if (!force) {
            while (!it.second.queue.empty()) {
            };
        }
        {
            std::lock_guard<std::mutex> lock_guard(it.second.mutex);
            auto itt = _eventMap.find(it.second.evenfd);
            if (itt == _eventMap.end()) {
                continue;
            }
            itt->second->setRunning(false);
        }
    }
}