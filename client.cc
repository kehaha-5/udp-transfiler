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
    auto clientConf = config::ClientConfig::getInstance().getConfig();
    client = make_unique<Client>(clientConf.ip.c_str(), clientConf.port);
    clientInteraction = make_unique<Interaction>();
    while (true) {
        inputCommand command = clientInteraction->input("udp-transfiler>");
        client->execCommand(command);
    }
}
