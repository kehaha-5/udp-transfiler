

#include "EventLoop.h"
#include "Logging.h"
#include "args.h"
#include "config/ServerConfig.h"
#include "file/server/Directory.h"
#include "log/Log.h"
#include "transfiler/Server.h"

int main(int argc, const char** argv) {
    if (getHelpAndShowHelp(argc, argv)) {
        return 1;
    }
    std::string configfile = "./server_config.ini";
    getArgsConfigFilePath(argc, argv, configfile);
    config::ServerConfig::getInstance().setConfigFile(configfile);

#ifdef DEBUG  // debug
    logConfig logconf = {logLever::debug, logAppender::console};
#else
    logConfig logconf = {logLever::info, logAppender::console};
#endif

    Log::getLog().setConfig(logconf);
    EventLoop event;
    transfiler::Server server(&event, config::ServerConfig::getInstance().getIp().c_str(), config::ServerConfig::getInstance().getPort(),
                              config::ServerConfig::getInstance().getThreadNum());
    file::server::Directory::getInstance().setFilePath();
    info_log("this file path is %s", file::server::Directory::getInstance().getFullPath().c_str());
    info_log("server configuration \n%s", config::ServerConfig::getInstance().getConfiguration().c_str());
    event.loop();
}
