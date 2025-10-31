#pragma once

#include <string>
#include <vector>

namespace SYSUtils {

inline std::vector<std::string> split(const std::string& s, char delim = ' ') {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == delim) {
            if (!cur.empty()) out.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

} // namespace SYSUtils
