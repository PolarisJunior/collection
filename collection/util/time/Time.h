
#pragma once
#include <chrono>
#include <cstdint>

class Time {
 public:
  /* Get Ms since starting */
  static std::chrono::milliseconds getMs();

  static std::chrono::seconds getSeconds();

  static uint32_t getTicks();
};