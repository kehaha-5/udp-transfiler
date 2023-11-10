#include <sys/eventfd.h>

#include <functional>
#include <memory>
#include <queue>
#include <thread>

#include "Logging.h"
#include "pool/ThreadPool.h"
using namespace pool;

void ThreadPool::queueHandle(int index) {
    auto queueItemIt = _msgQueues.find(index);
    debug_log("the evenfd is %d accpet this req in queueHandle", queueItemIt->second.evenfd);
    while (!queueItemIt->second.queue.empty()) {
        unsigned long long number;
        read(queueItemIt->second.evenfd, &number, sizeof(unsigned long long));
        queueMsgCb cd = queueItemIt->second.queue.front();
        cd();
        queueItemIt->second.queue.pop();
    }
};

void ThreadPool::threadRun(int index) {
    EventLoopPtr loop = std::make_unique<EventLoop>();
    QueueItem selfQueue = _msgQueues[index];
    loop->addIo(selfQueue.evenfd, std::bind(&ThreadPool::queueHandle, this, index), EPOLLIN);
    debug_log("sub thread start loop for queue");
    loop->loop();
}

ThreadPool::ThreadPool(int threadNum) {
    _threadNum = threadNum;
    for (int i = 0; i < threadNum; i++) {
        int evenfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
        exit_if(evenfd == -1, "thread create evenfd error ");
        Queue queue;
        QueueItem itemQueue = {evenfd, queue};
        _msgQueues.insert({i, itemQueue});

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
    queueItem->second.queue.push(cb);
    unsigned long long number = 1;
    /* https://man7.org/linux/man-pages/man2/eventfd.2.html
       A write(2) fails with the error EINVAL if the size of the
       supplied buffer is less than 8 bytes, or if an attempt is
       made to write the value 0xffffffffffffffff.
    */
    int len = write(queueItem->second.evenfd, &number, sizeof(unsigned long long));
    exit_if(len == -1, "add task to queue error");
    debug_log("the evenfd is %d accpet this req in sendMsg", queueItem->second.evenfd);
}
