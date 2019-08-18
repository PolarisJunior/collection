#pragma once

#include <string>
#include <utility>

class SdlLoader {
 public:
  static std::pair<bool, std::string> load();
};