
#include "game/ecs/Transform.h"

Transform::Transform(float x, float y, float z) : localPosition_(x, y, z) {}

Mat4 Transform::getModelMatrix() {
  if (matrixUpToDate) {
    return modelMatrix;
  } else {
    modelMatrix = Mat4::translate(localPosition_) * localRotation_.toMatrix() *
                  Mat4::scale(localScale_);
    matrixUpToDate = true;
    return modelMatrix;
  }
}

Mat4 Transform::getInverseModelMatrix() {
  Vec3 trans = -worldPosition();
  Vec3 sc = Vec3(Vec3::one() / worldScale());
  Quaternion rot = worldRotation().inverse();
  return Mat4::scale(sc) * rot.toMatrix() * Mat4::translate(trans);
  // return getModelMatrix().inverse();
}