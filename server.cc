#include <iostream>

#include "EventLoop.h"
#include "Logging.h"
#include "file/Directory.h"
#include "log/Log.h"
#include "transfiler/Server.h"

int main(int, char **) {
    logConfig logconf = {logLever::debug, logAppender::console};
    Log::setConfig(logconf);
    EventLoop event;
    transfiler::Server server(&event, "127.0.0.1", 23111);
    file::Directory::getInstance("./testFile");
    event.loop();
}
