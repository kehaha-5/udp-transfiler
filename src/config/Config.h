#ifndef SRC_CONFIG_CONFIG_H
#define SRC_CONFIG_CONFIG_H

#include <sys/types.h>

#include <regex>
#include <sstream>
#include <string>

#include "utils.h"
namespace config {

class Config {
   protected:
    bool findStrContain(std::string &str, std::string needle) {
        if (auto pos = str.find(needle); pos != std::string::npos) {
            if (auto annotationPos = str.find("#"); annotationPos != std::string::npos) {
                if (annotationPos < pos) {  //该内容被注释了
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    template <class T>  // T only u_short uint ulong std::string type
    bool getConfigData(std::string &line, T &res) {
        T data;
        auto eqPos = line.find("=") + 1;
        auto endPos = line.find("#");  // #号用来做注释
        if(endPos != std::string::npos){
            endPos = endPos - eqPos;
        }
        std::istringstream iss(utils::trim(line.substr(eqPos, endPos)));
        if (iss.str().empty()) {
            return false;
        }
        if (iss >> data) {
            res = data;
            return true;
        }
        return false;
    }

    bool isIpformat(const std::string &str) {
        std::regex ip_regex("((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}");
        return std::regex_match(str, ip_regex);
    }
};
}  // namespace config

#endif