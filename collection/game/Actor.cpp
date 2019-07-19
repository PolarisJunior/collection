#include "game/Actor.h"
#include "game/Component.h"

void Actor::attachComponent(Component* component, bool notify) {
  components.insert(component);
  if (notify) {
    component->attachToActor(this, false);
  }
}