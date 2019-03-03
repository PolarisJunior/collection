
#pragma once
#include <cstdint>
#include <ostream>

struct Rect {
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;

  friend std::ostream& operator<<(std::ostream& os, const Rect& rect);
};

inline std::ostream& operator<<(std::ostream& os, const Rect& rect) {
  os << "(" << rect.x << ", " << rect.y << ", " << rect.width << ", "
     << rect.height << ")";
  return os;
}