#pragma once

#include <math.h>
#include <ostream>

template <typename T>
class Vector2 {
 public:
  T x;
  T y;

  Vector2() = default;
  Vector2<T>(T x, T y);

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

  friend std::ostream& operator<<(std::ostream& out, const Vector2& vec);

  static Vector2 zero();
  static Vector2 right();
  static Vector2 left();
  static Vector2 up();
  static Vector2 down();
};

template <typename T>
inline Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2& other) {
  return Vector2(this->x + other.x, this->y + other.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2& other) {
  return Vector2(this->x - other.x, this->y - other.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator*(float scale) {
  return Vector2(this->x * scale, this->y * scale);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator/(float divisor) {
  return Vector2(this->x / divisor, this->y / divisor);
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2& other) {
  this->x += other.x;
  this->y += other.y;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2& other) {
  this->x -= other.x;
  this->y -= other.y;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator*=(float scale) {
  this->x *= scale;
  this->y *= scale;
  return *this;
}

template <typename T>
inline Vector2<T>& Vector2<T>::operator/=(float divisor) {
  this->x /= divisor;
  this->y /= divisor;
  return *this;
}

template <typename T>
inline bool Vector2<T>::operator==(const Vector2& other) {
  return this->x == other.x && this->y == other.y;
}

template <typename T>
inline float Vector2<T>::dot(const Vector2& other) {
  return ((this->x * other.x) + (this->y * other.y));
}

template <typename T>
inline float Vector2<T>::length() {
  return static_cast<float>(sqrt(dot(*this)));
}

template <typename T>
inline Vector2<T> Vector2<T>::normalized() {
  return *this / length();
}

template <typename T>
inline Vector2<T>& Vector2<T>::normalize() {
  *this /= length();
  return *this;
}

template <typename T>
inline bool Vector2<T>::equals(const Vector2& other, float delta) {
  return fabs(this->x - other.x) + fabs(this->y - other.y) < delta;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec) {
  out << "(" << vec.x << ", " << vec.y << ")";
  return out;
}

template <typename T>
inline Vector2<T> Vector2<T>::zero() {
  return Vector2(0, 0);
}

template <typename T>
inline Vector2<T> Vector2<T>::right() {
  return Vector2(1, 0);
}

template <typename T>
inline Vector2<T> Vector2<T>::left() {
  return Vector2(-1, 0);
}

template <typename T>
inline Vector2<T> Vector2<T>::up() {
  return Vector2(0, -1);
}

template <typename T>
inline Vector2<T> Vector2<T>::down() {
  return Vector2(0, 1);
}