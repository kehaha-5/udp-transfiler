#include <cctype>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

#include "Interaction.h"
#include "utils.h"

using namespace interaction;

const int LSSIZEW = 18;
const int LSLASTWRITETIMEW = 30;

void Interaction::help() {
    std::cout << "command:" << std::endl;
    std::cout << "\t" << COMMAND_LS << std::endl;
    std::cout << "\t" << COMMAND_DOWNLOADFILE << "\n\t\t" << DWONLOADFILE_FILE_ARG << "," << DWONLOADFILE_ALL_ARG << ","
              << DWONLOADFILE_USAGE << std::endl;
    std::cout << "\t"
              << "exit" << std::endl;
}

inputCommand Interaction::input(std::string cliName) {
    while (true) {
        std::cout << cliName;
        std::string command;
        char ch;
        while (std::cin.get(ch)) {
            if (ch == '\n') {
                break;
            }
            command += ch;
        }
        command = utils::trim(command);
        if (command.empty()) {
            continue;
        } else if (command == "help") {
            help();
        } else if (command == "exit") {
            exit(EXIT_SUCCESS);
        } else if (command == "ls") {
            return inputCommand(exceCommand::LS, "");
        } else if (command.find("downfile") != std::string::npos) {
            std::string arg;
            std::cout << "downfile" << std::endl;
            unsigned long pos;
            if ((pos = command.find(DWONLOADFILE_FILE_ARG)), pos != std::string::npos) {
                arg = command.substr(pos);
                auto fileName = utils::trim(arg.substr(interaction::DWONLOADFILE_FILE_ARG.size()));
                if (fileName.empty()) {
                    std::cout << "invalid args file name is empty" << std::endl;
                    continue;
                    ;
                }
            }
            if ((pos = command.find(DWONLOADFILE_ALL_ARG)), pos != std::string::npos) {
                arg = DWONLOADFILE_ALL_ARG;
            }
            if (arg.empty()) {
                std::cout << "miss arg please input help for usage" << std::endl;
                continue;
                ;
            }
            return inputCommand(exceCommand::DOWNLOADFILE, arg);
        } else {
            std::cout << "invalid command pleas input help for usage" << std::endl;
        }
    }
}

void Interaction::ls(file::server::filesInfo& fileinfos) {
    std::cout << std::setw(LSLASTWRITETIMEW) << std::left << "last_write_time";
    std::cout << std::setw(LSSIZEW) << std::left << "size";
    std::cout << std::left << "name";
    std::cout << std::endl;
    std::cout << std::setw(LSLASTWRITETIMEW) << std::left << "-----------------";
    std::cout << std::setw(LSSIZEW) << std::left << "-----";
    std::cout << std::left << "-----";
    std::cout << std::endl;
    for (auto it : fileinfos) {
        std::cout << std::setw(LSLASTWRITETIMEW) << std::left << it.last_write_time;
        std::cout << std::setw(LSSIZEW) << std::left << it.size;
        std::cout << std::left << it.name;
        std::cout << std::endl;
    }
}

void Interaction::showError(std::string msg) { std::cout << "\033[1;31m" << msg << "\033[0m" << std::endl; }

bool Interaction::confirm(std::string confirmMsg) {
    std::cout << confirmMsg << " [Y/N]:";
    char input[1] = {0};
    while (true) {
        std::cin.get(input[0]);
        if (input[0] == '\n') {
            std::cout << " [Y/N]:";
            continue;
        } else {
            break;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto res = tolower(input[0]);
    if (res == 121) {  // lower y
        return true;
    }
    return false;
}

void Interaction::showMsg(std::string msg) { std::cout << msg << std::flush; }
