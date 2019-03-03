#pragma once
#include <cstdint>
#include "../math/Vector2.h"

class Actor;

class Camera2 {
 public:
  Camera2();
  Camera2(float w, float h);

  void moveCamera(Vector2<float> newPos);
  void moveCamera(float x, float y);

  void smoothMoveCamera(Vector2<float> newPos, uint32_t ms);

  /* half of width and height */
  Vector2<float> getShape();
  /* Camera's position in the world, refers to center of camera view */
  Vector2<float> getPosition();
  float getWidth() { return width; }
  void setWidth(float w) { width = w; }

  float getHeight() { return height; }
  void setHeight(float h) { height = h; }

  Vector2<float> toScreenCoords(const Vector2<float>& worldPos);
  Vector2<float> toWorldCoords(const Vector2<float>& screenPos);

  void attachToActor(Actor* actor);
  void unAttach();

  void setAttachOffset(Vector2<float> offset);

 protected:
  Actor* attachedActor = nullptr;

  Vector2<float> position;
  Vector2<float> attachOffset;

  float width;
  float height;
};

inline Camera2::Camera2()
    : position(Vector2<float>(0, 0)), width(1), height(1) {}

inline Camera2::Camera2(float w, float h)
    : position(Vector2(0.0f, 0.0f)), width(w), height(h) {}

inline void Camera2::moveCamera(Vector2<float> newPos) {
  position = newPos;
}

inline void Camera2::moveCamera(float x, float y) {
  position.x = x;
  position.y = y;
}

inline void Camera2::setAttachOffset(Vector2<float> offset) {
  this->attachOffset = offset;
}

inline Vector2<float> Camera2::getShape() {
  return Vector2(width, height);
}

inline Vector2<float> Camera2::toScreenCoords(const Vector2<float>& worldPos) {
  Vector2 midpoint = getShape() / 2;
  Vector2 pos = getPosition();
  return Vector2(midpoint.x + worldPos.x - pos.x,
                 midpoint.y + worldPos.y - pos.y);
}

inline Vector2<float> Camera2::toWorldCoords(const Vector2<float>& screenPos) {
  Vector2 midpoint = getShape() / 2;
  Vector2 pos = getPosition();
  return Vector2(screenPos.x + pos.x - midpoint.x,
                 screenPos.y + pos.y - midpoint.y);
}

extern Camera2 mainCamera;