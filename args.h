#ifndef ARGS_H
#define ARGS_H

#include <cstring>
#include <iostream>
#include <string>

const std::string ARGV_CONFIG = "--config";
const std::string ARGV_HELP = "--help";

inline bool getArgsConfigFilePath(const int argc, const char** argv, std::string& configfile) {
    if (argc < 3) {
        return false;
    }
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], ARGV_CONFIG.c_str()) == 0) {
            if (argc < i + 1) {
                return false;
            }
            configfile = argv[i + 1];
            return true;
        }
    }
    return false;
}

inline bool getHelpAndShowHelp(const int argc, const char** args) {
    if (argc < 2) {
        return false;
    }
    if (std::strcmp(args[1], ARGV_HELP.c_str()) == 0) {
        std::cout << "--config \n"
                  << "\t set a special configfile \n";
        return true;
    }
    return false;
}

#endif