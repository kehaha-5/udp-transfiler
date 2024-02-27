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
            if (auto annotationPos = str.find("#"); annotationPos != std::string::npos) {
                if (annotationPos < pos) { //该内容被注释了
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    const std::string getConfigData(std::string &line) {
        auto eqPos = line.find("=") + 1;
        auto endPos = line.find("#");  // #号用来做注释
        return utils::trim(line.substr(eqPos, endPos));
    }

    template <class T>  // T only u_short uint ulong type
    bool getIntConfigData(std::string &line, T &res) {
        T data;
        auto eqPos = line.find("=") + 1;
        auto endPos = line.find("#");  // #号用来做注释
        std::istringstream iss(utils::trim(line.substr(eqPos, endPos)));
        if (iss >> data) {
            res = data;
            return true;
        }
        return false;
    }
};
}  // namespace config

#endif