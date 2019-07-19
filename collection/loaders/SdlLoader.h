#pragma once

#include <string>
#include <utility>

class SdlLoader {
 public:
  std::pair<bool, std::string> load();
};