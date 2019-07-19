
#include "util/stringUtils.h"
#include <sstream>
#include <vector>

std::vector<std::string> stringSplit(const std::string& s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (std::getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}