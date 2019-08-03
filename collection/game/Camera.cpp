
#include "game/Camera.h"
#include "Actor.h"
#include "game/ecs/PositionManager.h"

#include "math/Mathf.h"

#include "glm/gtc/matrix_transform.hpp"
#include "ui/Window.h"

Camera* Camera::mainCamera;

Camera::Camera()
    : width(Window::getMainWindow().getWidth()),
      height(Window::getMainWindow().getHeight()) {}

Mat4 Camera::getProjectionMatrix() {
  switch (projectionType) {
    case ProjectionType::PERSPECTIVE:
      glm::mat4 proj =
          glm::perspectiveFovLH(Mathf::deg2Rad * fieldOfView, width, height,
                                nearClipPlane, farClipPlane);
      return Mat4(proj);
    case ProjectionType::ORTHOGRAPHIC:
      glm::mat4 ortho =
          glm::orthoLH(0.f, 800.f, 0.f, 600.f, nearClipPlane, farClipPlane);
      return Mat4(ortho);
  }
}

Mat4 Camera::getViewMatrix() {
  return transform.getModelMatrix().inverse();
}

Camera& Camera::getMainCamera() {
  return *Camera::mainCamera;
}

void Camera::setMainCamera(Camera& cam) {
  mainCamera = &cam;
}