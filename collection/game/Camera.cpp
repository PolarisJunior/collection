
#include "game/Camera.h"
#include "Actor.h"
#include "game/ecs/PositionManager.h"

Camera* Camera::mainCamera;

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

Camera& Camera::getMainCamera() {
  return *Camera::mainCamera;
}

void Camera::setMainCamera(Camera& cam) {
  mainCamera = &cam;
}