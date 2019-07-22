
#include "math/Mathf.h"

#include <math.h>
#include <algorithm>
#include <cmath>

float Mathf::abs(float v) {
  return fabs(v);
}

float Mathf::max(float x, float y) {
  // bugged?
  // return std::max(x, y);
  return -1;
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

float Mathf::acos(float v) {
  return std::acos(v);
}

float Mathf::atan2(float y, float x) {
  return std::atan2(y, x);
}

float Mathf::asin(float v) {
  return std::asin(v);
}
