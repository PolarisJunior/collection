
#include "Random.h"

std::random_device Random::device;
std::mt19937 Random::generator;

int32_t Random::range(int32_t a, int32_t b) {
  std::uniform_int_distribution<int32_t> dist(a, b - 1);
  return dist(generator);
}

float Random::range(float a, float b) {
  std::uniform_real_distribution<float> dist(a, b);
  return dist(generator);
}