
#pragma once

#include <math.h>
#include <ostream>

class Vector3 {
 public:
  float x;
  float y;
  float z;

  Vector3(float x, float y, float z);

  Vector3 operator+(const Vector3& other);
  Vector3 operator-(const Vector3& other);
  Vector3 operator*(float scale);
  Vector3 operator/(float divisor);

  Vector3& operator+=(const Vector3& other);
  Vector3& operator-=(const Vector3& other);
  Vector3& operator*=(float scale);
  Vector3& operator/=(float divisor);

  bool operator==(const Vector3& other);

  friend std::ostream& operator<<(std::ostream& out, const Vector3& vec);

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

inline Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

inline Vector3 Vector3::operator+(const Vector3& other) {
  return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

inline Vector3 Vector3::operator-(const Vector3& other) {
  return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

inline Vector3 Vector3::operator*(float scale) {
  return Vector3(this->x * scale, this->y * scale, this->z * scale);
}

inline Vector3 Vector3::operator/(float divisor) {
  return Vector3(this->x / divisor, this->y / divisor, this->z / divisor);
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

inline Vector3& Vector3::operator*=(float scale) {
  this->x *= scale;
  this->y *= scale;
  this->z *= scale;
  return *this;
}

inline Vector3& Vector3::operator/=(float divisor) {
  this->x /= divisor;
  this->y /= divisor;
  this->z /= divisor;
  return *this;
}

inline bool Vector3::operator==(const Vector3& other) {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

inline Vector3 Vector3::normalized() {
  return *this / length();
}

inline Vector3& Vector3::normalize() {
  *this /= length();
}

inline float Vector3::length() {
  return static_cast<float>(sqrt(dot(*this)));
}

inline bool Vector3::equals(const Vector3& other, float delta = 0.00001) {
  return fabs(this->x - other.x) + fabs(this->y - other.y) +
             fabs(this->z - other.z) <
         delta;
}

inline float Vector3::dot(const Vector3& other) {
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

inline std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
  out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return out;
}

inline Vector3 Vector3::zero() {
  return Vector3(0, 0, 0);
}

inline Vector3 Vector3::right() {
  return Vector3(1, 0, 0);
}

inline Vector3 Vector3::left() {
  return Vector3(-1, 0, 0);
}

inline Vector3 Vector3::up() {
  return Vector3(0, -1, 0);
}

inline Vector3 Vector3::down() {
  return Vector3(0, 1, 0);
}

inline Vector3 Vector3::back() {
  return Vector3(0, 0, -1);
}

inline Vector3 Vector3::front() {
  return Vector3(0, 0, 1);
}