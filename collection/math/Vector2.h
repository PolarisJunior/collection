#pragma once

#include <math.h>
#include <ostream>

template <typename T>
class Vector2 {
 public:
  T x = 0;
  T y = 0;

  Vector2() = default;
  Vector2<T>(T x, T y);
  Vector2<T>(T k) : x(k), y(k) {}

  Vector2 operator+(const Vector2& other) const;
  Vector2 operator-(const Vector2& other) const;
  Vector2 operator*(float scale) const;
  Vector2 operator/(float divisor) const;
  Vector2 operator/(const Vector2& lhs) const;

  Vector2& operator+=(const Vector2& other);
  Vector2& operator-=(const Vector2& other);
  Vector2& operator*=(float scale);
  Vector2& operator/=(float divisor);

  bool operator==(const Vector2& other);

  Vector2 normalized();
  // normalizes the vector in place
  Vector2& normalize();
  float length();
  bool equals(const Vector2& other, float delta = 0.00001);

  float dot(const Vector2& other);

  // Needs to be inlined to work with templates
  friend std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
  }

  static Vector2 zero();
  static Vector2 right();
  static Vector2 left();
  static Vector2 up();
  static Vector2 down();
};

template <typename T>
inline Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2& other) const {
  return Vector2(this->x + other.x, this->y + other.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2& other) const {
  return Vector2(this->x - other.x, this->y - other.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator*(float scale) const {
  return Vector2(this->x * scale, this->y * scale);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator/(float divisor) const {
  return Vector2(this->x / divisor, this->y / divisor);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator/(const Vector2<T>& lhs) const {
  return Vector2(this->x / lhs.x, this->y / lhs.y);
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
  Vector2<T> ret = *this;
  ret.normalize();
  return ret;
}

template <typename T>
inline Vector2<T>& Vector2<T>::normalize() {
  if (length() > 0) {
    *this /= length();
  }
  return *this;
}

template <typename T>
inline bool Vector2<T>::equals(const Vector2& other, float delta) {
  return fabs(this->x - other.x) + fabs(this->y - other.y) < delta;
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
  return Vector2(0, 1);
}

template <typename T>
inline Vector2<T> Vector2<T>::down() {
  return Vector2(0, -1);
}

typedef Vector2<float> Vec2;