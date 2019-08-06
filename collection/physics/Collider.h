#pragma once

#include "game/ecs/Component.h"
#include "game/ecs/Transform.h"
#include "math/Ray.h"

class Collider {
 protected:
  //  returns a local space transformed ray
  Ray rayToLocal(const Ray& ray, Transform& t);
};
