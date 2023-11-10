#include <iostream>

#include "EventLoop.h"
#include "Logging.h"
#include "log/Log.h"
#include "udp/UpdServer.h"
int main(int, char **) {
    EventLoop event;
    logConfig logconf = {logLever::debug, logAppender::console};
    Log::setConfig(logconf);
    UdpServer server(&event, "127.0.0.1", 23111);
    event.loop();
}
