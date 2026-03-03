#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <string>
#include <vector>

namespace utils {
std::string trim(const std::string &s);
std::vector<std::string> delimSplit(const std::string &s, const std::string &delim);

std::chrono::system_clock::time_point parseDate(const std::string &s, const std::string &format);
} // namespace utils

#endif // UTILS_H
