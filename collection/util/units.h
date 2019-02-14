#pragma once
#include <cstdint>

/* Unit conversion functions */

inline double msToSeconds(uint32_t ms) {
  return static_cast<double>(ms) / 1000.0;
}

inline uint32_t secondsToMs(double seconds) {
  return static_cast<uint32_t>(seconds * 1000.0);
}
