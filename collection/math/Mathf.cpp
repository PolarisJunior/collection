
#include "math/Mathf.h"

#include <math.h>
#include <algorithm>
#include <cmath>

float Mathf::sqrt(float x) {
  return std::sqrt(x);
}

int32_t Mathf::abs(int32_t x) {
  return std::abs(x);
}

float Mathf::abs(float v) {
  return fabs(v);
}

float Mathf::max(float x, float y) {
  return std::max(x, y);
}

float Mathf::mod(float x, float y) {
  if (std::fabsf(y) <= 1.e-8f) {
    exit(EXIT_FAILURE);
    return 0.f;
  }

  float div = x / y;
  float quotient = fabsf(div) < 8388608.f ? Mathf::trunc(div) : div;

  float intPortion = y * quotient;
  if (fabsf(intPortion) > fabsf(x)) {
    intPortion = x;
  }

  return x - intPortion;
}

bool Mathf::inRange(float x, float a, float b) {
  return clamp(x, a, b) == x;
}

float Mathf::clamp(float x, float a, float b) {
  return std::clamp(x, a, b);
}

// clamp between 0 and 2pi
float Mathf::clampRad(float rad) {
  float res = Mathf::mod(rad, Mathf::pi * 2);

  if (res < 0) {
    res += Mathf::pi * 2;
  }

  return res;
}

// clamp between the values [-pi, pi]
float Mathf::normalizeRad(float rad) {
  float res = Mathf::clampRad(rad);
  if (res > Mathf::pi) {
    res -= Mathf::pi * 2;
  }

  return res;
}

float Mathf::trunc(float x) {
  return std::trunc(x);
}

float Mathf::cos(float v) {
  return std::cos(v);
}

float Mathf::sin(float v) {
  return std::sin(v);
}

float Mathf::tan(float x) {
  return std::tan(x);
}

float Mathf::acos(float v) {
  return std::acos(v);
}

float Mathf::atan(float x) {
  return std::atan(x);
}

float Mathf::atan2(float y, float x) {
  return std::atan2(y, x);
}

float Mathf::asin(float v) {
  return std::asin(v);
}

int32_t Mathf::sign(int32_t x) {
  return (0 < x) - (x < 0);
}