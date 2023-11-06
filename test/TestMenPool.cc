#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <thread>

#include "MenPool.h"

const int max_thread = 200;

void testWIthMen(std::shared_ptr<MenPool> menPool, int i) {
    NodePtr ptr = menPool->getMen();
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
    std::shared_ptr<MenPool> men = std::make_shared<MenPool>(100, 80, 100);
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