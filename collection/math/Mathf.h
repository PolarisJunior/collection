#pragma once

struct Mathf {
  static constexpr float pi = 3.14159265f;
  static constexpr float pi_4 = pi / 4.0f;
  static constexpr float pi_2 = pi / 2.0f;
  static constexpr float two_pi = pi * 2;
  static constexpr float deg2Rad = 2.f * pi / 360.f;
  static constexpr float rad2Deg = 180.f / pi;

  static constexpr float square(float x) { return x * x; }

  // static float clampAngle(float ang);
  // static float normalizeAngle(float ang);

  static float lerp(float a, float b, float t) { return a + t * (b - a); }

  static float clampRad(float rad);
  static float normalizeRad(float rad);

  static float mod(float x, float y);
  static float trunc(float x);

  static float max(float x, float y);
  static float abs(float v);

  static float cos(float v);
  static float sin(float v);

  static float acos(float v);
  static float atan2(float y, float x);
  static float asin(float v);
};
