#include "Actor.h"
#include "Component.h"

void Actor::attachComponent(Component* component, bool notify) {
  components[component->componentId] = component;
  if (notify) {
    component->attachToActor(this, false);
  }
}