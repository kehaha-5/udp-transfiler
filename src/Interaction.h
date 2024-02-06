#ifndef INTERACTION_H
#define INTERACTION_H
#include <string>

#include "file/server/Directory.h"

namespace interaction {

const std::string DWONLOADFILE_FILE_ARG = "--file";
const std::string DWONLOADFILE_ALL_ARG = "--all";
const std::string DWONLOADFILE_USAGE = "usage --file exist_file_name or --all (download all file)";
const std::string COMMAND_LS = "ls";
const std::string COMMAND_DOWNLOADFILE = "downfile";

enum exceCommand {
    LS = 0,
    DOWNLOADFILE,
};

struct inputCommand {
    inputCommand(exceCommand _command, std::string _args) : command(_command), args(_args){};
    exceCommand command;
    std::string args;
};
class Interaction {
   public:
    inputCommand input(std::string cliName);
    void showMsg(std::string &msg);
    void ls(file::server::filesInfo &fileinfos);
    void showError(std::string msg);
    bool confirm(std::string confirmMsg);

   private:
    void help();
};
}  // namespace interaction

#endif