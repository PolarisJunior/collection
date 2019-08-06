
#include "SphereCollider.h"
#include "math/Mathf.h"

bool SphereCollider::intersects(const Ray& ray) {
  constexpr float r = .5;
  constexpr float rSquared = r * r;

  Ray localRay = rayToLocal(ray, transform());

  Vec3 dir = localRay.direction();
  Vec3 origin = localRay.origin();

  // sphere is behind the ray
  if (origin.dot(origin) > rSquared && origin.dot(dir) >= 0) {
    return false;
  }

  float radicand =
      Mathf::square(dir.dot(origin)) - (origin.dot(origin) - Mathf::square(r));

  return radicand >= 0;
}