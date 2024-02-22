
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
    config::ServerConfig::getInstance().setConfigThreadNum(10);
     config::ServerConfig::getInstance().setConfigFilePath("./upload");
    transfiler::Server server(&event, config::ServerConfig::getInstance().getIp().c_str(), config::ServerConfig::getInstance().getPort(),
                              config::ServerConfig::getInstance().getThreadNum());
    file::server::Directory::getInstance().setFilePath();
    info_log("this file path is %s", file::server::Directory::getInstance().getFullPath().c_str());
    event.loop();
}
