#ifndef INTERACTION_H
#define INTERACTION_H
#include <string>
#include "file/server/Directory.h"

namespace interaction {
struct inputCommand {
    inputCommand(std::string _command, std::string _args) : command(_command), args(_args){};
    std::string command;
    std::string args;
};
class Interaction {
   public:
    inputCommand input(std::string cliName);
    void showMsg(std::string &msg);
    void ls(file::server::filesInfo &fileinfos);
    void showError(std::string msg);

   private:
    void help();
    std::string trim(const std::string &str);
};
}  // namespace interaction

#endif