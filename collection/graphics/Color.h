
#pragma once
#include <cstdint>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  // static Color WHITE;
};

namespace Colors {
extern Color WHITE;
extern Color BLACK;
}