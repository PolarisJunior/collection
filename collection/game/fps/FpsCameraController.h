#pragma once

#include "game/ecs/Component.h"

class FpsCameraController : public Component<FpsCameraController> {
 public:
  void update(float deltaTime);

 private:
};
