#pragma once

#include "Collider.h"
#include "game/ecs/Component.h"
#include "math/Ray.h"

class SphereCollider : public Collider, public Component<SphereCollider> {
 public:
  bool intersects(const Ray& ray);
};