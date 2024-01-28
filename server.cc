
#include "EventLoop.h"
#include "Logging.h"
#include "file/server/Directory.h"
#include "log/Log.h"
#include "transfiler/Server.h"

int main(int, char **) {
    logConfig logconf = {logLever::info, logAppender::console};
    Log::setConfig(logconf);
    EventLoop event;
    transfiler::Server server(&event, "127.0.0.1", 23111);
    file::server::Directory::getInstance().setFilePath("./testFile");
    info_log("this file path is %s", file::server::Directory::getInstance().getFullPath().c_str());
    event.loop();
}
