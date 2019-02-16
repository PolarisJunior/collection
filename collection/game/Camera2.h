#pragma once
#include <cstdint>
#include "../math/Vector2.h"

class Camera2 {
 public:
  Vector2 position;
  float width;
  float height;
  Camera2();
  Camera2(float w, float h);

  void moveCamera(Vector2 newPos);
  void moveCamera(float x, float y);

  void smoothMoveCamera(Vector2 newPos, uint32_t ms);

  Vector2 getMidPoint();

  Vector2 toScreenCoords(const Vector2& worldPos);
  Vector2 toWorldCoords(const Vector2& screenPos);

 protected:
};

inline Camera2::Camera2() : position(Vector2(0, 0)), width(1), height(1) {}

inline Camera2::Camera2(float w, float h)
    : position(Vector2(0, 0)), width(w), height(h) {}

inline void Camera2::moveCamera(Vector2 newPos) {
  position = newPos;
}

inline void Camera2::moveCamera(float x, float y) {
  position.x = x;
  position.y = y;
}

inline Vector2 Camera2::getMidPoint() {
  return Vector2(width / 2, height / 2);
}

inline Vector2 Camera2::toScreenCoords(const Vector2& worldPos) {
  Vector2 midpoint = getMidPoint();
  return Vector2(midpoint.x + worldPos.x - this->position.x,
                 midpoint.y + worldPos.y - this->position.y);
}

// inline Vector2 Camera2::toWorldCoords(const Vector2& screenPos) {}

extern Camera2 mainCamera;