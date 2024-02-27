#include <csignal>
#include <memory>
#include <string>

#include "Interaction.h"
#include "args.h"
#include "config/ClientConfig.h"
#include "log/Log.h"
#include "transfiler/Client.h"

using namespace std;
using namespace transfiler;
using namespace interaction;

unique_ptr<Client> client;
unique_ptr<Interaction> clientInteraction;

// Signal handler function
void signalHandler(int signum) {
    // No need to manually call saveInterruptionData here,
    // the destructor of interruptionSaver will be called when the program exits
    std::cout << "\nclear up ....." << std::endl;
    client->clearUp();
    std::cout << "clear up finish exit !!!!" << std::endl;
    std::exit(0);
}

int main(int argc, const char** argv) {
    if (getHelpAndShowHelp(argc, argv)) {
        return 1;
    }
    std::string configfile = "./client_config.ini";
    getArgsConfigFilePath(argc, argv, configfile);
    config::ClientConfig::getInstance().setConfigFile(configfile);

    logConfig logconf = {logLever::debug, logAppender::console};
    Log::setConfig(logconf);
    client = make_unique<Client>(config::ClientConfig::getInstance().getIp().c_str(), config::ClientConfig::getInstance().getPort());
    clientInteraction = make_unique<Interaction>();
    std::signal(SIGINT, signalHandler);
    while (true) {
        inputCommand command = clientInteraction->input("udp-transfiler>");
        client->execCommand(command);
    }
}
