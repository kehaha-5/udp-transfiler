#ifndef SRC_UTILS_H
#define SRC_UTILS_H
#include <cmath>
#include <string>

namespace utils {

inline std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    if (start == std::string::npos || end == std::string::npos) {
        // String contains only whitespace
        return "";
    }

    return str.substr(start, end - start + 1);
}

inline std::string humanReadable(std::uintmax_t size) {
    std::string res;
    res.resize(10, 0);
    double mantissa = size;
    int i{};
    for (; mantissa >= 1024.0; mantissa /= 1024.0, ++i) {  // 判断mantissa是否有单位默认单位是B，每个单位相差1024
    }
    std::sprintf(&res[0], "%.2f", std::ceil(mantissa * 10.0) / 10.0);
    res += i["BKMGTPE"];
    if (i > 0) {
        res += 'B';
    }
    return res;
}
}  // namespace utils

#endif