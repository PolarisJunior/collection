#pragma once
#include <cstdint>
#include "../math/Vector2.h"

class Camera2 {
 public:
  Camera2();

  void moveCamera(Vector2 newPos);
  void moveCamera(float x, float y);

  void smoothMoveCamera(Vector2 newPos, uint32_t ms);

 private:
  Vector2 position;
};

inline Camera2::Camera2() : position(Vector2(0, 0)) {}

inline void Camera2::moveCamera(Vector2 newPos) {
  position = newPos;
}

inline void Camera2::moveCamera(float x, float y) {
  position.x = x;
  position.y = y;
}

extern Camera2 mainCamera;