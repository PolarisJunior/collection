#pragma once

#include "game/ecs/Component.h"
#include "math/Vector3.h"

class RigidBody : public Component<RigidBody> {
 public:
  RigidBody() = default;

  float mass = 1;
  float drag = 10;
  float gravityScale = 1;

  void update(float deltaTime);

  void built() override;

 private:
  Vec3 velocity = Vec3::zero();
  Transform* transform_;
};
