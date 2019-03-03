
#pragma once
#include <cstdint>
#include <ostream>

template <typename T>
struct Rect {
  T x;
  T y;
  T width;
  T height;

  friend std::ostream& operator<<(std::ostream& os, const Rect& rect);
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Rect<T>& rect) {
  os << "(" << rect.x << ", " << rect.y << ", " << rect.width << ", "
     << rect.height << ")";
  return os;
}