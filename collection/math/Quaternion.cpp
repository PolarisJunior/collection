
#include "math/Quaternion.h"

#include <glm/gtc/quaternion.hpp>

#include <glm/detail/qualifier.hpp>
#include <glm/ext/quaternion_transform.hpp>

Quaternion::Quaternion(const Vec3& eulerRot) {
  glm::qua q(glm::vec3(eulerRot.pitch(), eulerRot.yaw(), eulerRot.roll()));
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}

Vec3 Quaternion::eulers() const {
  glm::qua q(x, y, z, w);
  glm::vec3 v = glm::eulerAngles(q);
  return Vec3(v.x, v.y, v.z);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
  glm::qua res = glm::qua(x, y, z, w) * glm::qua(rhs.x, rhs.y, rhs.z, rhs.w);
  return Quaternion(res.x, res.y, res.z, res.w);
}

const Quaternion Quaternion::identity(0, 0, 0, 1);