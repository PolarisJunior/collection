
#pragma once
#include <unordered_map>

class Component;

class Actor {
 public:
  float x;
  float y;
  void attachComponent(Component* component, bool notify = true);

  bool hasComponent(int32_t componentId);

  int32_t getId();

 private:
  std::unordered_map<int32_t, Component*> components;
  int32_t actorId;
};

inline bool Actor::hasComponent(int32_t componentId) {
  return components.count(componentId) > 0;
}

inline int32_t Actor::getId() {
  return actorId;
}