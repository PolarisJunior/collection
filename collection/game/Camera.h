#pragma once
#include <cstdint>
#include "game/ecs/Component.h"
#include "math/Mat4.h"
#include "math/Mathf.h"
#include "math/Ray.h"
#include "math/Vector2.h"
#include "util/Size2d.h"

class Camera : public Component<Camera>, public Size2d<float> {
 public:
  Camera();
  Camera(float w, float h);

  Mat4 getViewMatrix();
  Mat4 getProjectionMatrix();

  // origin is camera's world position
  Ray screenPointToRay(const Vec2& screenPos);

  float aspect() const { return width() / height(); }
  float hFov() const { return fieldOfView; }
  float vFov() const;

  static void setMainCamera(Camera& cam);
  static Camera& getMainCamera();

  enum class ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

  ProjectionType projectionType = ProjectionType::PERSPECTIVE;

 protected:
  float nearClipPlane = 0.1f;
  float farClipPlane = 1000.0f;

  // Field of view in degrees, horizontal
  float fieldOfView = 90;

  static Camera* mainCamera;
};

inline Camera::Camera(float w, float h) : Size2d(w, h) {}
