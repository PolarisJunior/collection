
#include "Component.h"
#include "Actor.h"

void Component::attachToActor(Actor* actor, bool notify) {
  attachedActor = actor;
  if (notify) {
    attachedActor->attachComponent(this, false);
  }

  onAttached(actor);
}

void Component::onAttached(Actor* actor) {}

void Component::onUnattached(Actor* actor) {}