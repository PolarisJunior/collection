
#include "game/ecs/Transform.h"

Transform::Transform(float x, float y, float z) : localPosition_(x, y, z) {}

Mat4 Transform::getModelMatrix() const {
  if (matrixUpToDate) {
    return modelMatrix;
  } else {
    modelMatrix = Mat4::translate(localPosition_) * localRotation_.toMatrix() *
                  Mat4::scale(localScale_);
    matrixUpToDate = true;
    return modelMatrix;
  }
}

Mat4 Transform::inverseScaleMatrix() const {
  return Mat4::scale(Vec3(Vec3::one() / worldScale()));
}

Mat4 Transform::inverseTranslateMatrix() const {
  return Mat4::translate(-worldPosition());
}

Mat4 Transform::getInverseModelMatrix() const {
  Quaternion rot = worldRotation().inverse();
  return inverseScaleMatrix() * rot.toMatrix() * inverseTranslateMatrix();
}