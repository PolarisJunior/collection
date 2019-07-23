
#include "game/ecs/Transform.h"

Mat4 Transform::getModelMatrix() {
  if (matrixUpToDate) {
    return modelMatrix;
  } else {
    // modelMatrix = Mat4::translate(localPosition_) * localRotation_.toMatrix()
    // *
    //               Mat4::scale(localScale_);
    // modelMatrix = Mat4::translate(-localPosition_) *
    // localRotation_.toMatrix() *
    //               Mat4::rotate(Mathf::pi, 1, 0, 0) *
    //               Mat4::rotate(Mathf::pi, 0, 1, 0) *
    //               Mat4::scale(localScale_);
    modelMatrix = Mat4::translate(-localPosition_) * localRotation_.toMatrix() *
                  Mat4::scale(localScale_);
    matrixUpToDate = true;
    return modelMatrix;
  }
}

Mat4 Transform::getInverseModelMatrix() {
  return getModelMatrix().inverse();
  // Vec3 t;
  // Vec3 s;
  // Quaternion r;

  // t = -localPosition_;

  // s.x = 1.0 / localScale_.x;
  // s.y = 1.0 / localScale_.y;
  // s.z = 1.0 / localScale_.z;

  // return Mat4::scale(s) * Mat4::translate(t);
}