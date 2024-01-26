#include <gtest/gtest.h>

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

#include "EventLoop.h"
#include "log/Log.h"

class TimerTest : public testing::Test {
   protected:
    void SetUp() {
        _loop = new EventLoop();
        _loop->startTimer();
        _thread = std::thread(std::bind(&TimerTest::runLoop, this));
        _thread.detach();
        logConfig logconf = {logLever::debug, logAppender::console};
        Log::setConfig(logconf);
    }
    void TearDown() {
        _loop->setRunning(false);
        delete _loop;
    }

   public:
    EventLoop* _loop;

   private:
    void runLoop() { _loop->loop(); }
    std::thread _thread;
};

TEST_F(TimerTest, getTimerOutTest) { ASSERT_EQ(_loop->getIntervalTimer(), 10); }

TEST_F(TimerTest, baseTest) {
    ASSERT_EQ(_loop->getIntervalTimer(), 10);
    int couter = 0;
    _loop->runAt(std::bind([&couter]() { couter++; }));
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    ASSERT_EQ(couter, 1);
}

TEST_F(TimerTest, functionalTest) {
    int counterRunAt = 0;
    int counterRunAfter = 0;
    int counterRunEvey = 0;
    _loop->runAt(std::bind([&counterRunAt]() { counterRunAt++; }));

    _loop->runAfter(20, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->runAfter(40, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->runAfter(60, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->runAfter(70, std::bind([&counterRunAfter]() { counterRunAfter++; }));

    _loop->runEvery(60, std::bind([&counterRunEvey]() { counterRunEvey++; }));

    std::this_thread::sleep_for(std::chrono::milliseconds(215));

    ASSERT_EQ(counterRunAt, 20);
    ASSERT_EQ(counterRunAfter, 4);
    ASSERT_EQ(counterRunEvey, 3);
}

TEST_F(TimerTest, cancelTimerTest) {
    int counterRunAt = 0;
    int counterRunAfter = 0;
    int counterRunEvey = 0;
    u_long resRunAt = _loop->runAt(std::bind([&counterRunAt]() { counterRunAt++; }));

    u_long resRunAfter1 = _loop->runAfter(20, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    u_long resRunAfter2 = _loop->runAfter(40, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    u_long resRunAfter3 = _loop->runAfter(60, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->cancelTimerEven(resRunAfter3);

    u_long resRunEvery = _loop->runEvery(80, std::bind([&counterRunEvey]() { counterRunEvey++; }));

    std::this_thread::sleep_for(std::chrono::milliseconds(235));

    _loop->cancelTimerEven(resRunAt);
    _loop->cancelTimerEven(resRunEvery);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ASSERT_EQ(counterRunAt, 22);    // 运行22次后取消
    ASSERT_EQ(counterRunAfter, 2);  // 运行3个 取消1个
    ASSERT_EQ(counterRunEvey, 2);   // 运行2次后取消
}

TEST_F(TimerTest, multiplyThreadTest) {
    std::vector<std::thread> threads;
    int threadNum = 30;
    threads.resize(threadNum);
    int couter = 0;
    auto loop = _loop;
    for (int i = 0; i < threadNum; i++) {
        threads[i] = std::thread(std::bind([loop, &couter]() { loop->runAfter(10, std::bind([&couter]() { couter++; })); }));
    }
    for (int i = 0; i < threadNum; i++) {
        threads[i].join();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    ASSERT_EQ(couter, threadNum);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}