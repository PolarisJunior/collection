
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

Vector2<float> Camera::getPosition() {
  if (isAttachedToEntity) {
    return positionManager->get(attachedEntity) + this->attachOffset;
  }
  if (attachedActor) {
    return Vector2(attachedActor->x, attachedActor->y) + this->attachOffset;
  } else {
    return position;
  }
}

void Camera::attachToActor(Actor* actor) {
  this->attachedActor = actor;
}

void Camera::unAttach() {
  if (this->attachedActor) {
    position.x = attachedActor->x;
    position.y = attachedActor->y;
    attachedActor = nullptr;
  }
}

Mat4 Camera::getProjectionMatrix() {
  switch (projectionType) {
    case ProjectionType::PERSPECTIVE:
      glm::mat4 proj = glm::perspective(fieldOfView, width / height,
                                        nearClipPlane, farClipPlane);
      return Mat4(proj);
    case ProjectionType::ORTHOGRAPHIC:
      glm::mat4 ortho =
          glm::ortho(0.f, 800.f, 0.f, 600.f, nearClipPlane, farClipPlane);
      return Mat4(ortho);
  }
}

Mat4 Camera::getViewMatrix() {
  return transform.getInverseModelMatrix();
}

Camera& Camera::getMainCamera() {
  return *Camera::mainCamera;
}

void Camera::setMainCamera(Camera& cam) {
  mainCamera = &cam;
}