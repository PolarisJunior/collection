
#include "game/Camera.h"
#include "game/ecs/PositionManager.h"

#include "math/Mathf.h"

#include "glm/gtc/matrix_transform.hpp"
#include "ui/Window.h"

Camera* Camera::mainCamera;

Camera::Camera()
    : Size2d(Window::getMainWindow().getWidth(),
             Window::getMainWindow().getHeight()) {}

Mat4 Camera::getProjectionMatrix() {
  switch (projectionType) {
    case ProjectionType::PERSPECTIVE:
      glm::mat4 proj =
          glm::perspectiveFovLH(Mathf::deg2Rad * fieldOfView, width(), height(),
                                nearClipPlane, farClipPlane);
      return Mat4(proj);
    case ProjectionType::ORTHOGRAPHIC:
      float aspect = width() / height();
      // Everything in the viewspace box is rendered
      // if we use orthographic we need to make the skybox bigger than the scene
      glm::mat4 ortho = glm::orthoLH<float>(-4, 4, -3, 3, -.1, 1000);
      return Mat4(ortho);
  }
}

Mat4 Camera::getViewMatrix() {
  return transform().getModelMatrix().inverse();
}

float Camera::vFov() const {
  return Mathf::atan(Mathf::tan(Mathf::deg2Rad * hFov() / 2) / aspect()) * 2 *
         Mathf::rad2Deg;
}

Ray Camera::screenPointToRay(const Vec2& screenPos) {
  Ray ray;
  ray.origin(transform().worldPosition());
  Vec3 dir = transform().forward();
  // theta is fov * (dist from center / width )
  Vec2 center(width() / 2, height() / 2);
  Vec2 fracOfScreen = (screenPos - center) / Vec2(width(), height());
  Vec2 theta = Vec2(hFov() * fracOfScreen.x, vFov() * fracOfScreen.y);

  Quaternion rotH(Mathf::deg2Rad * theta.x, Vec3::up());
  Quaternion rotV(Mathf::deg2Rad * theta.y, Vec3::right());
  ray.direction(rotH * rotV * dir);
  return ray;
}

Camera& Camera::getMainCamera() {
  return *Camera::mainCamera;
}

void Camera::setMainCamera(Camera& cam) {
  mainCamera = &cam;
}