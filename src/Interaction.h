#ifndef INTERACTION_H
#define INTERACTION_H
#include <string>

namespace interaction {
struct inputCommand {
    inputCommand(std::string _command, std::string _args) : command(_command), args(_args){};
    std::string command;
    std::string args;
};
class Interaction {
   public:
    inputCommand input(std::string cliName);
    void showMsg(std::string msg);

   private:
    void help();
    std::string trim(const std::string& str);
};
}  // namespace interaction

#endif