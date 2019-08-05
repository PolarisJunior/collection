#pragma once

#include "Vector3.h"

class Ray {
 public:
  Ray() = default;
  Ray(const Vec3& o, const Vec3& d) : origin_(o), direction_(d.normalized()) {}

  Vec3 origin() const { return origin_; }
  Vec3 direction() const { return direction_; }

  void origin(const Vec3& v) { origin_ = v; }
  void direction(const Vec3& v) { direction_ = v.normalized(); }

  Vec3 getPoint(float d) { origin() + direction() * d; }

 private:
  Vec3 origin_ = Vec3::zero();
  Vec3 direction_ = Vec3(1, 0, 0);
};
