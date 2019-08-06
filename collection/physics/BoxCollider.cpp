
#include "BoxCollider.h"
#include "math/Mathf.h"

bool BoxCollider::intersects(const Ray& ray) {
  constexpr float k = .5;

  Ray localRay = rayToLocal(ray, transform());
  Vec3 origin = localRay.origin();
  Vec3 dir = localRay.direction();

  // origin is not in the box
  bool inBox = !(Mathf::abs(origin.x) < k && Mathf::abs(origin.y) < k &&
                 Mathf::abs(origin.z) < k);
  //  box is behind the ray
  if (!inBox && (origin.dot(dir) >= 0)) {
    return false;
  }
}