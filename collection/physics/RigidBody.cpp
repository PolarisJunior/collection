
#include "RigidBody.h"
#include "Physics.h"
#include "math/Mathf.h"

void RigidBody::built() {
  transform_ = &transform();
}

void RigidBody::update(float deltaTime) {
  Vec3 acceleration = Vec3::down() * Physics::gravity * gravityScale;
  velocity += acceleration * deltaTime;

  // linear estimator for drag
  velocity *= Mathf::max((1 - deltaTime * drag), 0);

  transform_->translate(velocity * deltaTime);
}