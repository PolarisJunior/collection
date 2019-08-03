#pragma once
#include <cstdint>
#include "game/ecs/Transform.h"
#include "math/Mat4.h"
#include "math/Vector2.h"

class Camera {
 public:
  Camera();
  Camera(float w, float h);

  void smoothMoveCamera(Vector2<float> newPos, uint32_t ms);

  /* half of width and height */
  Vector2<float> getShape();
  /* Camera's position in the world, refers to center of camera view */
  // Vector2<float> getPosition();

  float getWidth() { return width; }
  void setWidth(float w) { width = w; }

  float getHeight() { return height; }
  void setHeight(float h) { height = h; }

  Vector2<float> toScreenCoords(const Vector2<float>& worldPos);
  Vector2<float> toWorldCoords(const Vector2<float>& screenPos);

  Mat4 getViewMatrix();
  Mat4 getProjectionMatrix();

  static void setMainCamera(Camera& cam);
  static Camera& getMainCamera();

  enum class ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

  Transform transform;
  ProjectionType projectionType = ProjectionType::PERSPECTIVE;

  // Field of view in degrees
  float fieldOfView = 60;
  float nearClipPlane = 0.1f;
  float farClipPlane = 1000.0f;

 protected:
  float width;
  float height;

  static Camera* mainCamera;
};

inline Camera::Camera(float w, float h) : width(w), height(h) {}

inline Vector2<float> Camera::getShape() {
  return Vector2(width, height);
}

inline Vector2<float> Camera::toScreenCoords(const Vector2<float>& worldPos) {
  return Vector2(0.f, 0.f);
  // Vector2 midpoint = getShape() / 2;
  // Vector2 pos = getPosition();
  // return Vector2(midpoint.x + worldPos.x - pos.x,
  //                midpoint.y + worldPos.y - pos.y);
}

inline Vector2<float> Camera::toWorldCoords(const Vector2<float>& screenPos) {
  return Vector2(0.f, 0.f);
  // Vector2 midpoint = getShape() / 2;
  // Vector2 pos = getPosition();
  // return Vector2(screenPos.x + pos.x - midpoint.x,
  //                screenPos.y + pos.y - midpoint.y);
}
