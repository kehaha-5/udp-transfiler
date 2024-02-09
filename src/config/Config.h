#ifndef SRC_CONFIG_CONFIG_H
#define SRC_CONFIG_CONFIG_H

#include <sys/types.h>

#include <sstream>
#include <string>

#include "utils.h"
namespace config {

class Config {
   protected:
    bool findStrContain(std::string &str, std::string needle) {
        if (auto pos = str.find(needle); pos != std::string::npos) {
            return true;
        }
        return false;
    }
    const std::string getConfigData(std::string &line) {
        auto eqPos = line.find("=") + 1;
        return trim(line.substr(eqPos, std::string::npos));
    }
    bool getIntConfigData(std::string &line, u_short &res) {
        auto eqPos = line.find("=") + 1;
        std::istringstream iss(trim(line.substr(eqPos, std::string::npos)));
        if (iss >> res) {
            return true;
        }
        return false;
    }
};
}  // namespace config

#endif