#pragma once

#include "Collider.h"
#include "SphereCollider.h"

class QuadCollider : public Collider, public Component<QuadCollider> {
 public:
  bool intersects(const Ray& ray);
  bool intersects(SphereCollider& collider);
};
