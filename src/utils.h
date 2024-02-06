#ifndef SRC_UTILS_H
#define SRC_UTILS_H
#include <string>

inline std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    if (start == std::string::npos || end == std::string::npos) {
        // String contains only whitespace
        return "";
    }

    return str.substr(start, end - start + 1);
}
#endif