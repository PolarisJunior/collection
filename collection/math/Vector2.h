#pragma once

#include <math.h>
#include <stdio.h>

class Vector2 {
 public:
  float x;
  float y;

  Vector2() = default;
  Vector2(float x, float y);

  Vector2 operator+(const Vector2& other);
  Vector2 operator-(const Vector2& other);
  Vector2 operator*(float scale);
  Vector2 operator/(float divisor);

  Vector2& operator+=(const Vector2& other);
  Vector2& operator-=(const Vector2& other);
  Vector2& operator*=(float scale);
  Vector2& operator/=(float divisor);

  bool operator==(const Vector2& other);

  Vector2 normalized();
  Vector2& normalize();
  float length();
  bool equals(const Vector2& other, float delta = 0.00001);

  float dot(const Vector2& other);

  void print();
  void println();

  static Vector2 zero();
  static Vector2 right();
  static Vector2 left();
  static Vector2 up();
  static Vector2 down();
};

inline Vector2::Vector2(float x, float y) : x(x), y(y) {}

inline Vector2 Vector2::operator+(const Vector2& other) {
  return Vector2(this->x + other.x, this->y + other.y);
}

inline Vector2 Vector2::operator-(const Vector2& other) {
  return Vector2(this->x - other.x, this->y - other.y);
}

inline Vector2 Vector2::operator*(float scale) {
  return Vector2(this->x * scale, this->y * scale);
}

inline Vector2 Vector2::operator/(float divisor) {
  return Vector2(this->x / divisor, this->y / divisor);
}

inline Vector2& Vector2::operator+=(const Vector2& other) {
  this->x += other.x;
  this->y += other.y;
  return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& other) {
  this->x -= other.x;
  this->y -= other.y;
  return *this;
}

inline Vector2& Vector2::operator*=(float scale) {
  this->x *= scale;
  this->y *= scale;
  return *this;
}

inline Vector2& Vector2::operator/=(float divisor) {
  this->x /= divisor;
  this->y /= divisor;
  return *this;
}

inline bool Vector2::operator==(const Vector2& other) {
  return this->x == other.x && this->y == other.y;
}

inline float Vector2::dot(const Vector2& other) {
  return ((this->x * other.x) + (this->y * other.y));
}

inline float Vector2::length() {
  return static_cast<float>(sqrt(dot(*this)));
}

inline Vector2 Vector2::normalized() {
  return *this / length();
}

inline Vector2& Vector2::normalize() {
  *this /= length();
  return *this;
}

inline bool Vector2::equals(const Vector2& other, float delta) {
  return fabs(this->x - other.x) + fabs(this->y - other.y) < delta;
}

inline void Vector2::print() {
  printf("(%f, %f)", x, y);
}

inline void Vector2::println() {
  printf("(%f, %f)\n", x, y);
}

inline Vector2 Vector2::zero() {
  return Vector2(0, 0);
}

inline Vector2 Vector2::right() {
  return Vector2(1, 0);
}

inline Vector2 Vector2::left() {
  return Vector2(-1, 0);
}

inline Vector2 Vector2::up() {
  return Vector2(0, -1);
}

inline Vector2 Vector2::down() {
  return Vector2(0, 1);
}