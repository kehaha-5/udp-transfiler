#include <gtest/gtest.h>

#include <chrono>
#include <functional>
#include <thread>

#include "EventLoop.h"

class TimerTest : public testing::Test {
   protected:
    void SetUp() {
        _loop = new EventLoop();
        _loop->startTimer();
        _thread = std::thread(std::bind(&TimerTest::runLoop, this));
        _thread.detach();
    }
    void TearDown() { delete _loop; }

   public:
    EventLoop* _loop;

   private:
    void runLoop() { _loop->loop(); }
    std::thread _thread;
};

TEST_F(TimerTest, setTimerOutTest) {
    ASSERT_EQ(_loop->getIntervalTimer(), 100);
    _loop->setIntervalTimer(0, 1000);
    ASSERT_EQ(_loop->getIntervalTimer(), 1000);
}

TEST_F(TimerTest, functionalTest) {
    _loop->setIntervalTimer(0, 10);
    int counterRunAt = 0;
    int counterRunAfter = 0;
    int counterRunEvey = 0;
    _loop->runAt(std::bind([&counterRunAt]() { counterRunAt++; }));

    _loop->runAfter(10, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->runAfter(20, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->runAfter(30, std::bind([&counterRunAfter]() { counterRunAfter++; }));

    _loop->runEvery(20, std::bind([&counterRunEvey]() { counterRunEvey++; }));
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    EXPECT_EQ(counterRunAt, 5);
    EXPECT_EQ(counterRunAfter, 3);
    EXPECT_EQ(counterRunEvey, 2);
}

TEST_F(TimerTest, cancelTimerTest) {
    _loop->setIntervalTimer(0, 10);
    int counterRunAt = 0;
    int counterRunAfter = 0;
    int counterRunEvey = 0;
    u_long resRunAt = _loop->runAt(std::bind([&counterRunAt]() { counterRunAt++; }));

    u_long resRunAfter1 = _loop->runAfter(10, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    u_long resRunAfter2 = _loop->runAfter(20, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    u_long resRunAfter3 = _loop->runAfter(30, std::bind([&counterRunAfter]() { counterRunAfter++; }));
    _loop->cancelTimerEven(resRunAfter3);

    u_long resRunEvery = _loop->runEvery(20, std::bind([&counterRunEvey]() { counterRunEvey++; }));

    std::this_thread::sleep_for(std::chrono::milliseconds(60));

    _loop->cancelTimerEven(resRunAt);
    _loop->cancelTimerEven(resRunEvery);

    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    EXPECT_EQ(counterRunAt, 5);     // 运行5次后取消
    EXPECT_EQ(counterRunAfter, 2);  // 运行3个 取消1个
    EXPECT_EQ(counterRunEvey, 2);   // 运行2次后取消
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}