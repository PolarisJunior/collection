
#pragma once
#include <unordered_map>

class Component;

class Actor {
 public:
  void attachComponent(Component* component, bool notify = true);

  bool hasComponent(int32_t componentId);

 private:
  std::unordered_map<int32_t, Component*> components;
};

inline bool Actor::hasComponent(int32_t componentId) {
  return components.count(componentId) > 0;
}