#include <cctype>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

#include "Interaction.h"
#include "config/ClientConfig.h"
#include "utils.h"

using namespace interaction;

const int LSSIZEW = 18;
const int LSLASTWRITETIMEW = 30;

void Interaction::help() {
    std::cout << "command:" << std::endl;
    std::cout << "\t" << COMMAND_LS << std::endl;
    std::cout << "\t" << COMMAND_DOWNLOADFILE << "\n\t\t" << DWONLOADFILE_FILE_ARG << "," << DWONLOADFILE_ALL_ARG << ","
              << DWONLOADFILE_USAGE << std::endl;
    std::cout << "\t" << COMMAND_GETCONFIG << std::endl;
    std::cout << "\n\t\t"
              << "show client configuration" << std::endl;
    std::cout << "\t"
              << "exit" << std::endl;
}

inputCommand Interaction::input(std::string cliName) {
    while (true) {
        std::printf("%s", cliName.c_str());
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
        } else if (strEq(command.c_str(), "help")) {
            help();
        } else if (strEq(command.c_str(), "exit")) {
            showMsg("bye!\n");
            std::exit(0);
        } else if (strEq(command.c_str(), "ls")) {
            return inputCommand(exceCommand::LS, "");
        } else if (command.find("downfile") != std::string::npos) {
            std::string arg;
            unsigned long pos;
            if ((pos = command.find(DWONLOADFILE_FILE_ARG)), pos != std::string::npos) {
                arg = command.substr(pos);
                auto fileName = utils::trim(arg.substr(interaction::DWONLOADFILE_FILE_ARG.size()));
                if (fileName.empty()) {
                    std::cout << "invalid args file name is empty" << std::endl;
                    continue;
                }
            }
            if ((pos = command.find(DWONLOADFILE_ALL_ARG)), pos != std::string::npos) {
                arg = DWONLOADFILE_ALL_ARG;
            }
            if (arg.empty()) {
                std::cout << "miss arg please input help for usage" << std::endl;
                continue;
            }
            return inputCommand(exceCommand::DOWNLOADFILE, arg);
        } else if (strEq(command.c_str(), "getConfig")) {
            showConfig();
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

void Interaction::showConfig() {
    std::cout << "\033[1;32m";
    std::cout << "  ip=" << config::ClientConfig::getInstance().getIp() << "\n";
    std::cout << "  port=" << config::ClientConfig::getInstance().getPort() << "\n";
    std::cout << "  filePath=" << config::ClientConfig::getInstance().getFilepath() << "\n";
    std::cout << "  downloadThreadNum=" << config::ClientConfig::getInstance().getDownloadThreadNum() << "\n";
    std::cout << "  maxResendPacketsNum=" << config::ClientConfig::getInstance().getMaxAckSet() << "\n";
    std::cout << "  maxDownloadSpeeds=" << utils::humanReadable(config::ClientConfig::getInstance().getMaxDownloadSpeeds()) << "\n";
    std::cout << "  packetsTimerOut=" << config::ClientConfig::getInstance().getPacketsTimerOut() << "\n";
    std::cout << "\033[0m";
}

void Interaction::showInLine(std::string& msg) {
    std::cout.seekp(0);
    std::cout << msg << std::flush;
}

bool Interaction::strEq(const char* str, const char* eqStr) { return std::strcmp(str, eqStr) == 0; }
