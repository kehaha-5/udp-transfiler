#include <iostream>

#include "EventLoop.h"
#include "Logging.h"
#include "udp/UpdServer.h"
int main(int, char **) {
    EventLoop event;
    UdpServer server(&event, "127.0.0.1", 23111);
    event.loop();
}
