#pragma once

#include <glm/mat4x4.hpp>
#include <ostream>
#include "math/Vector3.h"

class Mat4 {
 public:
  Mat4() = default;
  Mat4(const glm::mat4x4& m) { matrix = m; }

  Vec3 getRow3(int r);
  Vec3 getCol3(int c);

  Vec3 operator*(const Vec3& rhs);
  Mat4 operator*(const Mat4& rhs);

  static Mat4 identity();

  static Mat4 translate(const Vec3& offsets);
  static Mat4 translate(float x, float y, float z) {
    return translate(Vec3(x, y, z));
  }

  static Mat4 rotate(float rad, const Vec3& axis);
  static Mat4 rotate(float rad, float x, float y, float z) {
    return rotate(rad, Vec3(x, y, z));
  }

  static Mat4 scale(const Vec3& coef);
  static Mat4 scale(float x, float y, float z) { return scale(Vec3(x, y, z)); }

  friend std::ostream& operator<<(std::ostream& out, const Mat4& mat);

 private:
  glm::mat4x4 matrix;
};