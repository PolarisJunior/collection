
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
  // assert:  axis[] is unit length
  //
  // The quaternion representing the rotation is
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

Mat4 Quaternion::toMatrix() const {
  // Mat4 matrix = Mat4::zero;
  // float fTx = x + x;
  // float fTy = y + y;
  // float fTz = z + z;
  // float fTwx = fTx * w;
  // float fTwy = fTy * w;
  // float fTwz = fTz * w;
  // float fTxx = fTx * x;
  // float fTxy = fTy * x;
  // float fTxz = fTz * x;
  // float fTyy = fTy * y;
  // float fTyz = fTz * y;
  // float fTzz = fTz * z;

  // matrix.set(0, 0, 1.0f - (fTyy + fTzz));
  // matrix.set(0, 1, fTxy - fTwz);
  // matrix.set(0, 2, fTxz + fTwy);
  // matrix.set(1, 0, fTxy + fTwz);
  // matrix.set(1, 1, 1.0f - (fTxx + fTzz));
  // matrix.set(1, 2, fTyz - fTwx);
  // matrix.set(2, 0, fTxz - fTwy);
  // matrix.set(2, 1, fTyz + fTwx);
  // matrix.set(2, 2, 1.0f - (fTxx + fTyy));

  // matrix.set(0, 0, 1.0f - (fTyy + fTzz));
  // matrix.set(1, 0, fTxy - fTwz);
  // matrix.set(2, 0, fTxz + fTwy);
  // matrix.set(0, 1, fTxy + fTwz);
  // matrix.set(1, 1, 1.0f - (fTxx + fTzz));
  // matrix.set(2, 1, fTyz - fTwx);
  // matrix.set(0, 2, fTxz - fTwy);
  // matrix.set(1, 2, fTyz + fTwx);
  // matrix.set(2, 2, 1.0f - (fTxx + fTyy));
  // return matrix;

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