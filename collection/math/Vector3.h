
#pragma once

#include <math.h>
#include <cstdint>
#include <ostream>

template <class Numeric>
class Vector3 {
 public:
  Numeric x = 0;
  Numeric y = 0;
  Numeric z = 0;

  Vector3() = default;
  Vector3(Numeric x, Numeric y, Numeric z);

  Vector3 operator+(const Vector3& other) const;
  Vector3 operator-(const Vector3& other) const;
  Vector3 operator*(float scale) const;
  Vector3 operator/(float divisor) const;

  Vector3 operator-() const;

  Vector3& operator+=(const Vector3& other);
  Vector3& operator-=(const Vector3& other);
  Vector3& operator*=(const Vector3& other);
  Vector3& operator*=(float scale);
  Vector3& operator/=(float divisor);

  bool operator==(const Vector3& other);

  friend std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  }

  Vector3 normalized() const;
  Vector3& normalize();
  float length();
  bool equals(const Vector3& other, float delta = 0.00001);

  float dot(const Vector3& other) const;
  Vector3 cross(const Vector3& other) const;

  float pitch() const;
  float yaw() const;
  float roll() const;

  static Vector3 zero();
  static Vector3 one();
  static Vector3 right();
  static Vector3 left();
  static Vector3 up();
  static Vector3 down();
  static Vector3 front();
  static Vector3 back();
  static Vector3 forward();
  static Vector3 backward();
};

template <class Numeric>
inline Vector3<Numeric>::Vector3(Numeric x, Numeric y, Numeric z)
    : x(x), y(y), z(z) {}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator+(
    const Vector3<Numeric>& other) const {
  return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator-(
    const Vector3<Numeric>& other) const {
  return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator-() const {
  return Vector3(-x, -y, -z);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator*(float scale) const {
  return Vector3(this->x * scale, this->y * scale, this->z * scale);
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::operator/(float divisor) const {
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
inline Vector3<Numeric>& Vector3<Numeric>::operator*=(
    const Vector3<Numeric>& other) {
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
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
inline Vector3<Numeric> Vector3<Numeric>::normalized() const {
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
inline float Vector3<Numeric>::dot(const Vector3<Numeric>& other) const {
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

template <class Numeric>
inline Vector3<Numeric> Vector3<Numeric>::cross(
    const Vector3<Numeric>& other) const {
  return Vector3<Numeric>(y * other.z - z * other.y, z * other.x - x * other.z,
                          x * other.y - y * other.x);
}

template <class Numeric>
float Vector3<Numeric>::pitch() const {
  return this->x;
}

template <class Numeric>
float Vector3<Numeric>::yaw() const {
  return this->y;
}

template <class Numeric>
float Vector3<Numeric>::roll() const {
  return this->z;
}

inline Vector3<float> Vector3<float>::zero() {
  return Vector3(0, 0, 0);
}

inline Vector3<float> Vector3<float>::one() {
  return Vector3(1, 1, 1);
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
  return Vector3(0, 1, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::down() {
  return Vector3(0, -1, 0);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::back() {
  return Vector3(0, 0, -1);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::front() {
  return Vector3(0, 0, 1);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::backward() {
  return Vector3(0, 0, -1);
}

template <typename Numeric>
inline Vector3<Numeric> Vector3<Numeric>::forward() {
  return Vector3(0, 0, 1);
}

using Vec3 = Vector3<float>;