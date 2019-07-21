
#include "game/ecs/Transform.h"

Mat4 Transform::getModelMatrix() {
  if (matrixUpToDate) {
    return modelMatrix;
  } else {
    modelMatrix = Mat4::translate(localPosition_) * Mat4::scale(localScale_) *
                  Mat4::rotate(localEulers_.x, Vec3::right()) *
                  Mat4::rotate(localEulers_.y, Vec3::up()) *
                  Mat4::rotate(localEulers_.z, Vec3::front());
    matrixUpToDate = true;
    return modelMatrix;
  }
}