#include <iostream>

#include "Interaction.h"

using namespace interaction;

void Interaction::help() {
    std::cout << "command:" << std::endl;
    std::cout << "\t"
              << "ls" << std::endl;
    std::cout << "\t"
              << "downfile --file,--all" << std::endl;
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

        if (command.empty()) {
            continue;
        } else if (command == "help") {
            help();
        } else if (command == "exit") {
            exit(EXIT_SUCCESS);
        } else if (command == "ls") {
            return inputCommand("ls", "");
        } else if (command.find("downfile") != std::string::npos) {
            std::string arg;
            std::cout << "downfile" << std::endl;
            unsigned long pos;
            if ((pos = command.find("--file")), pos != std::string::npos) {
                arg = command.substr(pos + 6);
                arg = trim(arg);
            }
            if ((pos = command.find("--all")), pos != std::string::npos) {
                arg = "--all";
            }
            std::cout << "arg" << arg << std::endl;
            return inputCommand("downfile", arg);
        } else {
            std::cout << "inval command pleas input help" << std::endl;
        }
    }
}

std::string Interaction::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    if (start == std::string::npos || end == std::string::npos) {
        // String contains only whitespace
        return "";
    }

    return str.substr(start, end - start + 1);
}