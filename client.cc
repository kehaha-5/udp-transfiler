#include <memory>
#include <string>

#include "Interaction.h"
#include "config/ClientConfig.h"
#include "log/Log.h"
#include "transfiler/Client.h"

using namespace std;
using namespace transfiler;
using namespace interaction;

unique_ptr<Client> client;
unique_ptr<Interaction> clientInteraction;

int main(int, char**) {
    logConfig logconf = {logLever::debug, logAppender::console};
    Log::setConfig(logconf);
    config::ClientConfig::getInstance().setConfigDownloadThreadNum(1);
    client = make_unique<Client>(config::ClientConfig::getInstance().getIp().c_str(), config::ClientConfig::getInstance().getPort());
    clientInteraction = make_unique<Interaction>();
    while (true) {
        inputCommand command = clientInteraction->input("udp-transfiler>");
        client->execCommand(command);
    }
}
