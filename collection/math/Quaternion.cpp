
#include "math/Quaternion.h"

#include <glm/gtc/quaternion.hpp>

Quaternion::Quaternion(const Vec3& eulerRot) {
  float SP, SY, SR;
  float CP, CY, CR;

  const float pitch = Mathf::mod(eulerRot.pitch(), Mathf::two_pi);
  const float yaw = Mathf::mod(eulerRot.yaw(), Mathf::two_pi);
  const float roll = Mathf::mod(eulerRot.roll(), Mathf::two_pi);

  SP = Mathf::sin(pitch);
  CP = Mathf::cos(pitch);
  SY = Mathf::sin(yaw);
  CY = Mathf::cos(yaw);
  SR = Mathf::sin(roll);
  CR = Mathf::cos(roll);

  this->x = CR * SP * SY - SR * CP * CY;
  this->y = -CR * SP * CY - SR * CP * SY;
  this->z = CR * CP * SY - SR * SP * CY;
  this->w = CR * CP * CY + SR * SP * SY;
}

Vec3 Quaternion::eulers() const {
  const float singularityTest = z * x - w * y;
  const float yawY = 2.f * (w * z + x * y);
  const float yawX = (1.f - 2.f * (Mathf::square(y) + Mathf::square(z)));

  const float SINGULARITY_THRESHOLD = 0.4999995f;
  Vec3 res;
  float pitch;  // x axis
  float yaw;    // y axis
  float roll;   // z axis

  if (singularityTest < -SINGULARITY_THRESHOLD) {
    pitch = -Mathf::pi_2;
    yaw = Mathf::atan2(yawY, yawX);
    roll = Mathf::normalizeRad(yaw - (2.f * Mathf::atan2(x, w)));
  } else if (singularityTest > SINGULARITY_THRESHOLD) {
    pitch = Mathf::pi_2;
    yaw = Mathf::atan2(yawY, yawX);
    roll = Mathf::normalizeRad(yaw - (2.f * Mathf::atan2(x, w)));
  } else {
    pitch = Mathf::asin(2.f * (singularityTest));
    yaw = Mathf::atan2(yawY, yawX);
    roll = Mathf::atan2(-2.f * (w * x + y * z),
                        (1.f - 2.f * (Mathf::square(x) + Mathf::square(y))));
  }

  res.x = pitch;
  res.y = yaw;
  res.z = roll;
  return res;
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
  const Quaternion& lhs = *this;
  return Quaternion(
      (float)((double)lhs.w * (double)rhs.x + (double)lhs.x * (double)rhs.w +
              (double)lhs.y * (double)rhs.z - (double)lhs.z * (double)rhs.y),
      (float)((double)lhs.w * (double)rhs.y + (double)lhs.y * (double)rhs.w +
              (double)lhs.z * (double)rhs.x - (double)lhs.x * (double)rhs.z),
      (float)((double)lhs.w * (double)rhs.z + (double)lhs.z * (double)rhs.w +
              (double)lhs.x * (double)rhs.y - (double)lhs.y * (double)rhs.x),
      (float)((double)lhs.w * (double)rhs.w - (double)lhs.x * (double)rhs.x -
              (double)lhs.y * (double)rhs.y - (double)lhs.z * (double)rhs.z));
}

const Quaternion Quaternion::identity(0, 0, 0, 1);