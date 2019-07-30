#pragma once
#include <cstdint>
#include <random>

class Random {
 public:
  //  returns a value between a and b both inclusive
  static float range(float a, float b);
  // returns value between a (inclusive) and b (exclusive)
  static int32_t range(int32_t a, int32_t b);

 private:
  static std::random_device device;
  static std::mt19937 generator;
};