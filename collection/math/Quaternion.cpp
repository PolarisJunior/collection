
#include "math/Quaternion.h"

#include <glm/gtc/quaternion.hpp>

#include <glm/detail/qualifier.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <sstream>

glm::qua<float, glm::qualifier::defaultp> toGlmQua(const Quaternion& q) {
  glm::qua<float, glm::qualifier::defaultp> gq;
  gq.x = q.x;
  gq.y = q.y;
  gq.z = q.z;
  gq.w = q.w;
  return gq;
}

void setFromGlmQua(glm::qua<float, glm::qualifier::defaultp> gq,
                   Quaternion& q) {
  q.x = gq.x;
  q.y = gq.y;
  q.z = gq.z;
  q.w = gq.w;
}

Quaternion::Quaternion(const Vec3& eulerRot) {
  glm::qua q(glm::vec3(eulerRot.pitch(), eulerRot.yaw(), eulerRot.roll()));
  setFromGlmQua(q, *this);
}

Quaternion::Quaternion(float x, float y, float z) : Quaternion(Vec3(x, y, z)) {}

Quaternion::Quaternion(float rfAngle, const Vec3& rkAxis) {
  // axis[] is unit length
  //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
  Vec3 axis = rkAxis.normalized();

  float fHalfAngle(0.5 * rfAngle);
  float fSin = Mathf::sin(fHalfAngle);
  w = Mathf::cos(fHalfAngle);
  x = fSin * axis.x;
  y = fSin * axis.y;
  z = fSin * axis.z;
}

Vec3 Quaternion::eulers() const {
  glm::qua q(x, y, z, w);
  glm::vec3 v = glm::eulerAngles(q);
  return Vec3(v.x, v.y, v.z);
}

Quaternion Quaternion::inverse() const {
  float norm = w * w + x * x + y * y + z * z;

  if (norm > 0.0) {
    float invNorm = 1.0 / norm;
    return Quaternion(-x * invNorm, -y * invNorm, -z * invNorm, w * invNorm);
  }
  // Error
  return Quaternion(0, 0, 0, 0);
}

Mat4 Quaternion::toMatrix() const {
  glm::qua gq = toGlmQua(*this);
  glm::mat4x4 m = glm::toMat4(gq);
  return Mat4(m);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
  return Quaternion(w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                    w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
                    w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
                    w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
  Quaternion q = *this * rhs;
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
  return *this;
}

std::string Quaternion::toString() const {
  std::stringstream ss;
  ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
  return ss.str();
}

const Quaternion Quaternion::identity(0, 0, 0, 1);