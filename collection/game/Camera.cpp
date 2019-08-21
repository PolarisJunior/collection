
#include "game/Camera.h"
#include "game/ecs/PositionManager.h"

#include "math/Mathf.h"

#include <iostream>
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
      // glm::mat4 ortho = glm::orthoLH<float>(-4, 4, -3, 3, -.1, 1000);
      glm::mat4 ortho = glm::orthoLH<float>(-1, 1, -1, 1, 0, 1000);
      return Mat4(ortho);
  }
}

Mat4 Camera::getViewMatrix() {
  return transform().getInverseModelMatrix();
}

float Camera::vFov() const {
  return Mathf::atan(Mathf::tan(Mathf::deg2Rad * hFov() / 2) / aspect()) * 2 *
         Mathf::rad2Deg;
}

Ray Camera::screenPointToRay(const Vec2& screenPos) {
  // convert screen to normalized device coordinates, and then transform by
  // perspective matrix to get view space position
  Vec3 ndc((screenPos.x / width() - .5) * 2, -(screenPos.y / height() - .5) * 2,
           -1);
  Ray ray(transform().worldPosition(), transform().worldRotation().toMatrix() *
                                           getInverseProjectionMatrix() * ndc);
  return ray;
}

Camera& Camera::getMainCamera() {
  return *Camera::mainCamera;
}

void Camera::setMainCamera(Camera& cam) {
  mainCamera = &cam;
}