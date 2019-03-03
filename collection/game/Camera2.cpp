#include "Camera2.h"
#include "Actor.h"

Vector2<float> Camera2::getPosition() {
  if (attachedActor) {
    return Vector2(attachedActor->x, attachedActor->y) + this->attachOffset;
  } else {
    return position;
  }
}

void Camera2::attachToActor(Actor* actor) {
  this->attachedActor = actor;
}

void Camera2::unAttach() {
  if (this->attachedActor) {
    position.x = attachedActor->x;
    position.y = attachedActor->y;
    attachedActor = nullptr;
  }
}