#pragma once

#include <glm/mat4x4.hpp>
#include <ostream>
#include "math/Vector3.h"

class Mat4 {
 public:
  Mat4() = default;
  Mat4(const glm::mat4x4& m) { matrix = m; }

  Vec3 getRow3(int32_t r);
  Vec3 getCol3(int32_t c);

  void set(int32_t r, int32_t c, float v);
  // inverts the 4th column of the first 3 rows
  // this is helpful for adjusting to opengl coordinates
  void invertTranslate();

  Vec3 operator*(const Vec3& rhs) const;
  Mat4 operator*(const Mat4& rhs) const;

  Mat4 inverse() const;

  const float* dataPointer() const;

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

  static const Mat4 zero;
  static const Mat4 identity;

  glm::mat4x4 matrix = glm::mat4(0.0f);

 private:
};