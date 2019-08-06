
#include "Collider.h"

Ray Collider::rayToLocal(const Ray& ray, Transform& t) {
  Mat4 inverseModel = t.getInverseModelMatrix();
  return Ray(
      inverseModel * ray.origin(),
      t.inverseScaleMatrix() * (t.worldRotation().inverse() * ray.direction()));
}