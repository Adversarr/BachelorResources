#pragma once

#include <string>
#include <strstream>
#include <vector>

namespace mias {

std::string strtolower(std::string s);
std::size_t find_first(const std::string& s, char c, size_t start = 0);
std::size_t find_first_nws(const std::string& s, size_t start = 0);
std::size_t find_first_ws(const std::string& s, size_t start = 0);

std::vector<std::string> split(std::string s, char c);

uint32_t atoi(const std::string &s);
}
