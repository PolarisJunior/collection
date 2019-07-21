
#include "game/ecs/Transform.h"

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