#include <iostream>

#include "EventLoop.h"
#include "Logging.h"
#include "log/Log.h"
#include "udp/UpdServer.h"

int runAtWithCancelIndex;
EventLoop event;

void runAt() { info_log("i am the run at function"); }

void runAtWithCancel() { info_log("i am the run at function but i will be cancel after 10s") }

void runEvery() { info_log("i am the run every function"); }

void runAfter() {
    info_log("i am the run after function will run after 10s");
    event.cancelTimerEven(runAtWithCancelIndex);
    info_log("i cancel the runAtWithCancel !!!");
}

int main(int, char **) {
    logConfig logconf = {logLever::debug, logAppender::console};
    Log::setConfig(logconf);
    UdpServer server(&event, "127.0.0.1", 23111);
    int runAtIndex = event.runAt(std::bind(runAt));
    runAtWithCancelIndex = event.runAt(std::bind(runAtWithCancel));
    int runAfterIndex = event.runAfter(10, std::bind(runAfter));
    info_log("something will run after 10s");
    int runEveryIndex = event.runEvery(5, std::bind(runEvery));
    info_log("something will run loop after 5s");
    event.loop();
}
