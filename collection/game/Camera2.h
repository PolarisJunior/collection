#pragma once
#include <cstdint>
#include "../math/Vector2.h"

class Actor;

class Camera2 {
 public:
  float width;
  float height;
  Camera2();
  Camera2(float w, float h);

  void moveCamera(Vector2 newPos);
  void moveCamera(float x, float y);

  void smoothMoveCamera(Vector2 newPos, uint32_t ms);

  Vector2 getMidPoint();
  Vector2 getPosition();

  Vector2 toScreenCoords(const Vector2& worldPos);
  Vector2 toWorldCoords(const Vector2& screenPos);

  void attachToActor(Actor* actor);
  void unAttach();

  void setAttachOffset(Vector2 offset);

 protected:
  Actor* attachedActor = nullptr;
  Vector2 position;
  Vector2 attachOffset;
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

inline void Camera2::setAttachOffset(Vector2 offset) {
  this->attachOffset = offset;
}

inline Vector2 Camera2::getMidPoint() {
  return Vector2(width / 2, height / 2);
}

inline Vector2 Camera2::toScreenCoords(const Vector2& worldPos) {
  Vector2 midpoint = getMidPoint();
  Vector2 pos = getPosition();
  return Vector2(midpoint.x + worldPos.x - pos.x,
                 midpoint.y + worldPos.y - pos.y);
}

inline Vector2 Camera2::toWorldCoords(const Vector2& screenPos) {
  Vector2 midpoint = getMidPoint();
  Vector2 pos = getPosition();
  return Vector2(screenPos.x + pos.x - midpoint.x,
                 screenPos.y + pos.y - midpoint.y);
}

extern Camera2 mainCamera;