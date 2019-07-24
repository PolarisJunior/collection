#pragma once

#include <cstdint>
#include <functional>
#include "math/Vector3.h"

class Hash {
 public:
  template <class T>
  static void hashCombine(std::size_t& seed, const T v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
};

// example of forward declaring template and defining a hash function
// template <typename T>
// class Vector3;
