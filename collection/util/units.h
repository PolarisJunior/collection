#pragma once
#include <cstdint>

/* Unit conversion functions */

inline double msToSeconds(uint32_t ms) {
  return static_cast<double>(ms) / 1000.0;
}
