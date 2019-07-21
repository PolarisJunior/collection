#pragma once

#include "math/Mat4.h"
#include "math/Vector3.h"

class Transform {
 public:
  Transform() = default;

  Vec3 localPosition() { return this->localPosition_; }
  Vec3 localEulerAngles() { return this->localEulers_; }
  Vec3 localScale() { return this->localScale_; }

  void translate(Vec3 offset) {
    localPosition_ += offset;
    matrixUpToDate = false;
  }

  void scale(Vec3 coef) {
    localScale_ *= coef;
    matrixUpToDate = false;
  }

  Mat4 getModelMatrix();

 private:
  // Vec3 localPosition_ = Vec3::zero();
  // Vec3 localScale_ = Vec3::one();
  // Vec3 localEulers_ = Vec3::zero();
  Vec3 localPosition_ = Vec3::zero();
  Vec3 localScale_ = Vec3::one();
  Vec3 localEulers_ = Vec3::zero();

  bool matrixUpToDate = false;
  Mat4 modelMatrix;
};
