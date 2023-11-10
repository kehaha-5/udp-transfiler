#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <thread>

#include "pool/MemPool.h"

const int max_thread = 200;
using namespace pool;
void testWIthMen(std::shared_ptr<MemPool> menPool, int i) {
    MemPtr ptr = menPool->getMem();
    char *msg = ptr->get();
    char msgData[100];
    std::sprintf(msgData, "12345678910 and i is %d", i);
    memcpy(msg, &msgData, 100);
    auto id = std::this_thread::get_id();
    // std::cout << "msg is " << msg << "the men addr is " << (void*)ptr->men << std::endl;
    printf("msg is %s the men addr is %p \n", msg, msg);
    menPool->clear(ptr);
}

void testWithOutMen() {
    char *msg[1024] = {};
    memcpy(msg, "12345678910\0", 100);
    std::cout << "men context is  " << msg << std::endl;
}

int main(int, char **) {
    std::shared_ptr<MemPool> men = std::make_shared<MemPool>(100, 80, 85);
    std::thread thread[max_thread];
    std::cout << "total size of " << men->getTotalSize() << std::endl;
    for (int i = 0; i < max_thread; i++) {
        thread[i] = std::thread(testWIthMen, men, i);
    }
    for (int i = 0; i < max_thread; i++) {
        thread[i].join();
    }
    std::cout << "total size of " << men->getTotalSize() << std::endl;
    std::printf("end \n");
}