#include "utils.h"
#include <algorithm>
#include <cctype>

namespace utils {
std::string trim(const std::string &s) {
    // find first and last non whitespace char
    auto start = std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isspace(c); });

    // need base to turn back into forward iterator
    auto end =
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isspace(c); }).base();
    return (start < end) ? std::string(start, end) : std::string{};
}
} // namespace utils
