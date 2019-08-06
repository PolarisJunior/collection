#pragma once

#include "Collider.h"

class QuadCollider : public Collider, public Component<QuadCollider> {
 public:
  bool intersects(const Ray& ray);
};
