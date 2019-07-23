#pragma once
#include <cstdint>
#include "game/ecs/Transform.h"
#include "math/Mat4.h"
#include "math/Vector2.h"

class Actor;
class PositionManager;

class Camera {
 public:
  Camera();
  Camera(float w, float h);

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

  void attachToEntity(uint32_t eid);
  void unAttachFromEntity();
  void setPositionManager(PositionManager& posManager);

  void setAttachOffset(Vector2<float> offset);

  Mat4 getViewMatrix();
  // adjusted for opengl coordinates
  Mat4 getLeftViewMatrix();
  Mat4 getProjectionMatrix();

  static void setMainCamera(Camera& cam);
  static Camera& getMainCamera();

  enum class ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

  Transform transform;
  ProjectionType projectionType = ProjectionType::PERSPECTIVE;

  // Field of view height in degrees
  float fieldOfView = 45;
  float nearClipPlane = 0.1f;
  float farClipPlane = 1000.0f;

 protected:
  Actor* attachedActor = nullptr;
  uint32_t attachedEntity = 0;
  PositionManager* positionManager;
  bool isAttachedToEntity = false;

  Vector2<float> position;
  Vector2<float> attachOffset;

  float width;
  float height;

  static Camera* mainCamera;
};

inline Camera::Camera(float w, float h)
    : position(Vector2(0.0f, 0.0f)), width(w), height(h) {}

inline void Camera::moveCamera(Vector2<float> newPos) {
  position = newPos;
}

inline void Camera::moveCamera(float x, float y) {
  position.x = x;
  position.y = y;
}

inline void Camera::setAttachOffset(Vector2<float> offset) {
  this->attachOffset = offset;
}

inline void Camera::attachToEntity(uint32_t eid) {
  attachedEntity = eid;
  isAttachedToEntity = true;
}

inline void Camera::unAttachFromEntity() {
  isAttachedToEntity = false;
}

inline void Camera::setPositionManager(PositionManager& posManager) {
  positionManager = &posManager;
}

inline Vector2<float> Camera::getShape() {
  return Vector2(width, height);
}

inline Vector2<float> Camera::toScreenCoords(const Vector2<float>& worldPos) {
  Vector2 midpoint = getShape() / 2;
  Vector2 pos = getPosition();
  return Vector2(midpoint.x + worldPos.x - pos.x,
                 midpoint.y + worldPos.y - pos.y);
}

inline Vector2<float> Camera::toWorldCoords(const Vector2<float>& screenPos) {
  Vector2 midpoint = getShape() / 2;
  Vector2 pos = getPosition();
  return Vector2(screenPos.x + pos.x - midpoint.x,
                 screenPos.y + pos.y - midpoint.y);
}
