#include <gtest/gtest.h>
#include <sys/types.h>

#include <exception>
#include <functional>
#include <ostream>
#include <thread>
#include <unordered_set>
#include <vector>

#include "transfiler/AckRandom.h"

TEST(AckTest, functionalTest) {
    const int loopNum = 500;
    int delItemNum = 50;
    std::unordered_set<u_long> unqiueAck;
    for (int i = 0; i < loopNum; i++) {
        unqiueAck.insert(transfiler::AckRandom::getAck());
    }
    EXPECT_EQ(unqiueAck.size(), loopNum);
    EXPECT_EQ(unqiueAck.size(), transfiler::AckRandom::getAckMapSzie());

    int j = 1;
    for (auto ack : unqiueAck) {
        ASSERT_EQ(1, transfiler::AckRandom::releasesAck(ack));
        if (j == delItemNum) {
            EXPECT_EQ(loopNum - delItemNum, transfiler::AckRandom::getAckMapSzie());
            delItemNum += 50;
        }
        j++;
    }

    EXPECT_EQ(j - 1, loopNum);
    ASSERT_EQ(transfiler::AckRandom::getAckMapSzie(), 0);
}

TEST(AckTest, multiplyThreadTest) {
    const int threadNum = 10;
    const int threadLoopNum = 30;
    std::vector<std::thread> threads;
    threads.resize(threadNum);
    try {
        for (int i = 0; i < threadNum; i++) {
            threads[i] = std::thread(std::bind([threadLoopNum]() {
                std::unordered_set<u_long> unqiueAck;
                for (int i = 0; i < threadLoopNum; i++) {
                    unqiueAck.insert(transfiler::AckRandom::getAck());
                }
                ASSERT_EQ(unqiueAck.size(), threadLoopNum);
            }));
        }

        for (int i = 0; i < threadNum; i++) {
            threads[i].join();
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        throw e;
    }

    ASSERT_EQ(transfiler::AckRandom::getAckMapSzie(), threadNum * threadLoopNum);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}