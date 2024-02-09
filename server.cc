
#include "EventLoop.h"
#include "Logging.h"
#include "config/ServerConfig.h"
#include "file/server/Directory.h"
#include "log/Log.h"
#include "transfiler/Server.h"

int main(int, char **) {
    logConfig logconf = {logLever::debug, logAppender::console};
    Log::setConfig(logconf);
    EventLoop event;
    auto servConf = config::ServerConfig::getInstance().getConfig();
    transfiler::Server server(&event, servConf.ip.c_str(), servConf.port);
    file::server::Directory::getInstance().setFilePath("./testFile");
    info_log("this file path is %s", file::server::Directory::getInstance().getFullPath().c_str());
    event.loop();
}
