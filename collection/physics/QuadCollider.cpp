
#include "QuadCollider.h"
#include "math/Mathf.h"

bool QuadCollider::intersects(const Ray& ray) {
  constexpr float r = .5;

  Ray localRay = rayToLocal(ray, transform());
  Vec3 origin = localRay.origin();
  Vec3 dir = localRay.dir();
  float nDotM = Vec3::up().dot(dir);
  // parallel to quad
  if (nDotM == 0) {
    return false;
  }

  float nDotB = Vec3::up().dot(origin);

  float t = -nDotB / nDotM;
  // behind ray
  if (t < 0) {
    return false;
  }

  Vec3 intersection = origin + dir * t;
  return Mathf::abs(intersection.x) < r && Mathf::abs(intersection.z) < r;
}