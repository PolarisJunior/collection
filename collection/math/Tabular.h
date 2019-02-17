
#pragma once
#include <cstdint>
#include <utility>

class Tabular {
 public:
  Tabular() = default;
  Tabular(int32_t w, int32_t h);

  int32_t getIndex(int32_t col, int32_t row);
  std::pair<int32_t, int32_t> getCoord(int32_t index);

  int32_t getTotalCells();

  int32_t width;
  int32_t height;
};

inline Tabular::Tabular(int32_t w, int32_t h) : width(w), height(h) {}

inline int32_t Tabular::getIndex(int32_t col, int32_t row) {
  return col + row * width;
}

inline std::pair<int32_t, int32_t> Tabular::getCoord(int32_t index) {
  std::pair<int32_t, int32_t> coord;
  coord.first = index % width;
  coord.second = index / width;
  return coord;
}

inline int32_t Tabular::getTotalCells() {
  return width * height;
}