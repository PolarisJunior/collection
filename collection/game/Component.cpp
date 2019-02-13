
#include "Component.h"
#include "Actor.h"

void Component::attachToActor(Actor* actor, bool notify) {
  attachedActor = actor;
  if (notify) {
    attachedActor->attachComponent(this, false);
  }
}

void Component::onAttached() {}

void Component::onUnattached() {}