
#pragma once
#include <cstdint>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

namespace Colors {
const Color WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
const Color BLACK = {0, 0, 0, 0xFF};
const Color RED = {0xFF, 0, 0, 0xFF};
const Color GREEN = {0, 0xFF, 0, 0xFF};
const Color BLUE = {0, 0, 0xFF, 0xFF};
}  // namespace Colors