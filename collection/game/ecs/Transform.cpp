
#include "game/ecs/Transform.h"

Mat4 Transform::getModelMatrix() {
  if (matrixUpToDate) {
    return modelMatrix;
  } else {
    modelMatrix = Mat4::translate(localPosition_) * Mat4::scale(localScale_);
    matrixUpToDate = true;
    return modelMatrix;
  }
}