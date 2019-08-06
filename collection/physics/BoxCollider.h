#pragma once

#include "Collider.h"
#include "game/ecs/Component.h"
#include "math/Ray.h"

class BoxCollider : public Collider, public Component<BoxCollider> {
 public:
  bool intersects(const Ray& ray);
};
