#pragma once

#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vector3.h"

class Transform {
 public:
  Transform() = default;

  Vec3 localPosition() const { return this->localPosition_; }
  Quaternion localRotation() const { return this->localRotation_; }
  // Vec3 localEulerAngles() { return this->localEulers_; }
  Vec3 localScale() const { return this->localScale_; }

  void translate(const Vec3& offset) {
    localPosition_ += offset;
    matrixUpToDate = false;
  }

  void translate(float x, float y, float z) { translate(Vec3(x, y, z)); }

  void scale(const Vec3& coef) {
    localScale_ *= coef;
    matrixUpToDate = false;
  }

  void scale(float x, float y, float z) { scale(Vec3(x, y, z)); }

  void rotate(float rad, const Vec3& axis) { rotate(Quaternion(rad, axis)); }

  void rotate(float rad, float x, float y, float z) {
    rotate(rad, Vec3(x, y, z));
  }

  void rotate(const Quaternion& quat) {
    localRotation_ *= quat;
    matrixUpToDate = false;
  }

  Mat4 getModelMatrix();
  Mat4 getInverseModelMatrix();

  Vec3 right() const { return localRotation_ * Vec3::right(); }
  Vec3 left() const { return localRotation_ * Vec3::left(); }
  Vec3 up() const { return localRotation_ * Vec3::up(); }
  Vec3 down() const { return localRotation_ * Vec3::down(); }
  Vec3 front() const { return localRotation_ * Vec3::front(); }
  Vec3 back() const { return localRotation_ * Vec3::back(); }

 private:
  Vec3 localPosition_ = Vec3::zero();
  Vec3 localScale_ = Vec3::one();
  Quaternion localRotation_ = Quaternion::identity;

  bool matrixUpToDate = false;
  Mat4 modelMatrix;
};