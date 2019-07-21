
#pragma once

#include <string>
#include "math/Mat4.h"
#include "math/Mathf.h"
#include "math/Vector3.h"

class Quaternion {
 public:
  float x = 0;
  float y = 0;
  float z = 0;
  float w = 1;

  Quaternion() = default;
  // explicit set values
  Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  // euler radians
  Quaternion(const Vec3& eulerRot);
  // euler radians
  Quaternion(float x, float y, float z);
  // angle axis
  Quaternion(float rad, const Vec3& axis);

  Vec3 eulers() const;

  Vec3 degrees() const {
    Vec3 res = eulers();
    res.x *= Mathf::rad2Deg;
    res.y *= Mathf::rad2Deg;
    res.z *= Mathf::rad2Deg;
    return res;
  }

  Mat4 toMatrix() const;

  Vec3 operator*(const Vec3& v) const {
    Vec3 Q(x, y, z);
    Vec3 T = Q.cross(v) * 2.0f;
    Vec3 res = v + (T * w) + Q.cross(T);
    return res;
  }

  Quaternion operator*(const Quaternion& rhs) const;

  Quaternion& operator*=(const Quaternion& rhs);

  std::string toString() const;

  static const Quaternion identity;
};
