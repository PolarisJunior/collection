
#include "math/Mat4.h"

#include <glm/gtx/transform.hpp>

Vec3 fromGlmVec(const glm::vec4& v) {
  return Vec3(v.x, v.y, v.z);
}

Vec3 fromGlmVec(const glm::vec3& v) {
  return Vec3(v.x, v.y, v.z);
}

glm::vec3 toGlmVec(const Vec3& v) {
  return glm::vec3(v.x, v.y, v.z);
}

Vec3 Mat4::getRow3(int r) {
  return Vec3(matrix[0][r], matrix[1][r], matrix[2][r]);
}

Vec3 Mat4::getCol3(int c) {
  return Vec3(matrix[c][0], matrix[c][1], matrix[c][2]);
}

Mat4 Mat4::identity() {
  return Mat4(glm::mat4x4(1.0f));
}

Mat4 Mat4::translate(const Vec3& offsets) {
  return glm::translate(toGlmVec(offsets));
}

Mat4 Mat4::scale(const Vec3& coef) {
  return Mat4(glm::scale(toGlmVec(coef)));
}

Mat4 Mat4::rotate(float rad, const Vec3& axis) {
  glm::mat4 m = glm::rotate(rad, toGlmVec(axis));
  return Mat4(m);
}

Vec3 Mat4::operator*(const Vec3& rhs) {
  glm::vec4 res(rhs.x, rhs.y, rhs.z, 1.0f);
  res = matrix * res;

  return fromGlmVec(res);
}

Mat4 Mat4::operator*(const Mat4& rhs) {
  return Mat4(this->matrix * rhs.matrix);
}

std::ostream& operator<<(std::ostream& out, const Mat4& mat) {
  out << "[ ";
  for (int i = 0; i < 4; i++) {
    out << "(";
    for (int j = 0; j < 3; j++) {
      // stored as column by row so have to swap
      // column j, row i
      out << mat.matrix[j][i] << ", ";
    }
    out << mat.matrix[3][i];
    out << ") ";
  }
  out << "]";
  return out;
}