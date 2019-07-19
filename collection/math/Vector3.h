
#pragma once

#include <math.h>
#include <cstdint>
#include <ostream>

template <class Numeric>
class Vector3 {
 public:
  Numeric x;
  Numeric y;
  Numeric z;

  Vector3() = default;
  Vector3(Numeric x, Numeric y, Numeric z);

  Vector3 operator+(const Vector3& other);
  Vector3 operator-(const Vector3& other);
  Vector3 operator*(float scale);
  Vector3 operator/(float divisor);

  Vector3& operator+=(const Vector3& other);
  Vector3& operator-=(const Vector3& other);
  Vector3& operator*=(float scale);
  Vector3& operator/=(float divisor);

  bool operator==(const Vector3& other);

  friend std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  }

  Vector3 normalized();
  Vector3& normalize();
  float length();
  bool equals(const Vector3& other, float delta = 0.00001);

  float dot(const Vector3& other);

  static Vector3 zero();
  static Vector3 right();
  static Vector3 left();
  static Vector3 up();
  static Vector3 down();
  static Vector3 front();
  static Vector3 back();
};

template <class Numeric>
inline Vector3<Numeric>::Vector3(Numeric x, Numeric y, Numeric z)
    : x(x), y(y), z(z) {}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator+(
    const Vector3<Numeric>& other) {
  return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator-(
    const Vector3<Numeric>& other) {
  return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator*(float scale) {
  return Vector3(this->x * scale, this->y * scale, this->z * scale);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator/(float divisor) {
  return Vector3(this->x / divisor, this->y / divisor, this->z / divisor);
}

template <class Numeric>
inline Vector3<Numeric>& Vector3<Numeric>::operator+=(
    const Vector3<Numeric>& other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

template <class Numeric>
inline Vector3<Numeric>& Vector3<Numeric>::operator-=(
    const Vector3<Numeric>& other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

template <class Numeric>
inline Vector3<Numeric>& Vector3<Numeric>::operator*=(float scale) {
  this->x *= scale;
  this->y *= scale;
  this->z *= scale;
  return *this;
}

template <class Numeric>
inline Vector3<Numeric>& Vector3<Numeric>::operator/=(float divisor) {
  this->x /= divisor;
  this->y /= divisor;
  this->z /= divisor;
  return *this;
}

template <class Numeric>
inline bool Vector3<Numeric>::operator==(const Vector3<Numeric>& other) {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::normalized() {
  Vector3<Numeric> ret = *this;
  ret.normalize();
  return ret;
}

template <class Numeric>
inline Vector3<Numeric>& Vector3<Numeric>::normalize() {
  if (length() > 0) {
    *this /= length();
  }
  return *this;
}

template <class Numeric>
inline float Vector3<Numeric>::length() {
  return static_cast<float>(sqrt(dot(*this)));
}

template <class Numeric>
inline bool Vector3<Numeric>::equals(const Vector3<Numeric>& other,
                                     float delta) {
  return fabs(this->x - other.x) + fabs(this->y - other.y) +
             fabs(this->z - other.z) <
         delta;
}

template <class Numeric>
inline float Vector3<Numeric>::dot(const Vector3<Numeric>& other) {
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

inline Vector3<float> Vector3<float>::zero() {
  return Vector3(0, 0, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::right() {
  return Vector3(1, 0, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::left() {
  return Vector3(-1, 0, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::up() {
  return Vector3(0, -1, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::down() {
  return Vector3(0, 1, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::back() {
  return Vector3(0, 0, -1);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::front() {
  return Vector3(0, 0, 1);
}

using Vec3 = Vector3<float>;