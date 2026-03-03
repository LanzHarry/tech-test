#include "utils.h"
#include <algorithm>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace utils {
std::string trim(const std::string &s) {
    // find first and last non whitespace char
    auto start = std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isspace(c); });

    // need base to turn back into forward iterator
    auto end =
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isspace(c); }).base();
    return (start < end) ? std::string(start, end) : std::string{};
}

std::vector<std::string> delimSplit(const std::string &s, const std::string &delim) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delim);
    while (end != std::string::npos) {
        tokens.push_back(trim(s.substr(start, end - start)));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    tokens.push_back(trim(s.substr(start)));
    return tokens;
}

std::chrono::system_clock::time_point parseDate(const std::string &s, const std::string &format) {
    std::tm tm = {};
    std::istringstream dateStream(s);
    dateStream >> std::get_time(&tm, format.c_str());
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}
} // namespace utils
