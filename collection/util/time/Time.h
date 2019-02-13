
#pragma once
#include <cstdint>

class Time {
 public:
  /* Get Ms since starting */
  static uint32_t getMs();
  static uint32_t getSeconds();
};