#include <memory>
#include <string>

#include "Interaction.h"
#include "Logging.h"
#include "log/Log.h"
#include "transfiler/Client.h"

using namespace std;
using namespace transfiler;
using namespace interaction;

unique_ptr<Client> client;
unique_ptr<Interaction> clientInteraction;

int main(int, char**) {
    logConfig logconf = {logLever::info, logAppender::console};
    Log::setConfig(logconf);
    client = make_unique<Client>("127.0.0.1", 23111);
    clientInteraction = make_unique<Interaction>();
    while (true) {
        clientInteraction->input("ftp>");
    }
}
