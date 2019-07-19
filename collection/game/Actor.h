
#pragma once
#include <algorithm>
#include <set>

class Component;

class Actor {
 public:
  float x;
  float y;
  /* Attach component to this actor, if notify is true then component becomes
   * aware */
  void attachComponent(Component* component, bool notify = true);
  void attachComponent(Component& component, bool notify = true);
  bool hasComponent(Component* comp);

  int32_t getId();

 private:
  std::set<Component*> components;
  int32_t actorId;
};

inline void Actor::attachComponent(Component& comp, bool notify) {
  attachComponent(&comp, notify);
}

inline bool Actor::hasComponent(Component* comp) {
  return components.find(comp) != components.end();
}

inline int32_t Actor::getId() {
  return actorId;
}
