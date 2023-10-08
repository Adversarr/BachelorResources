#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <spdlog/spdlog.h>

#include <sstream>
#include <iomanip>
#include <string>

namespace mias {
std::string strtolower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return tolower(c); });
  return s;
}

std::size_t find_first(const std::string &s, char c, size_t start) {
  if (start >= s.length()) {
    return start;
  }
  while (s[start] != c) {
    start += 1;
    if (start == s.length()) {
      break;
    }
  }

  return start;
}

std::size_t find_first_ws(const std::string &s, size_t start) {
  if (start >= s.length()) {
    return start;
  }
  while (!std::isspace(s[start])) {
    start += 1;
    if (start == s.length()) {
      break;
    }
  }

  return start;
}

std::size_t find_first_nws(const std::string &s, size_t start) {
  if (start >= s.length()) {
    return start;
  }
  while (std::isspace(s[start])) {
    start += 1;
    if (start == s.length()) {
      break;
    }
  }

  return start;
}

std::vector<std::string> split(std::string s, char c) {
  std::string current;
  std::vector<std::string> retval;
  for (auto x : s) {
    if (x != c) {
      current.push_back(x);
    } else {
      retval.push_back(current);
      current.clear();
    }
  }
  if (!current.empty()) {
    retval.push_back(current);
  }
  for (const auto& s: retval) {
    spdlog::debug("Splitted: {}", s);
  }
  return retval;
}

uint32_t atoi(const std::string &s) {
  bool hex = false;
  if (s.length() > 2) {
    if (s.substr(0, 2) == "0x") {
      hex = true;
    }
  }
  uint32_t retval;
  if (hex) {
    std::istringstream iss(s);
    iss >> std::setbase(16) >> retval;
  } else {
    retval = std::atoi(s.c_str());
  }
  return retval;
}
}
