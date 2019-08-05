
#include "SphereCollider.h"
#include "math/Mathf.h"

bool SphereCollider::intersects(const Ray& ray) {
  Transform& trans = transform();

  Mat4 inverseModel = trans.getInverseModelMatrix();
  Ray localRay{inverseModel * ray.origin(), inverseModel * ray.direction()};
  float r = .5;

  Vec3 dir = localRay.direction();
  Vec3 origin = localRay.origin();
  float radicand =
      Mathf::square(dir.dot(origin)) - (origin.dot(origin) - Mathf::square(r));

  return radicand >= 0;
}