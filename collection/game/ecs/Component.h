#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include "GameObject.h"
#include "Transform.h"

// Uses CRTP to create the static map per template instance

template <typename Derived>
class Component {
  using RealComponent = Derived;

 public:
  Component() = default;
  Component(const Component& c) = delete;

  Component& operator=(const Component& other) = delete;
  Component& operator=(Component&& other) = delete;

  GameObject& gameObject() { return *gameObject_; }
  Transform& transform() { return gameObject().transform(); }

 private:
  GameObject* gameObject_ = nullptr;

  inline static std::unordered_map<int32_t, RealComponent> objectIdToComponent;

  friend class GameObject;

  static RealComponent& addComponent(GameObject& go) {
    // inserts the element in place with no copying
    RealComponent& comp =
        (objectIdToComponent
             .emplace(std::piecewise_construct,
                      std::forward_as_tuple(go.getInstanceId()),
                      std::forward_as_tuple())
             .first)
            ->second;
    comp.gameObject_ = &go;
    return comp;
  }

  static void destroyComponent(int32_t id) { objectIdToComponent.erase(id); }

  static RealComponent& getComponent(int32_t id) {
    return objectIdToComponent.at(id);
  }

  static bool hasComponent(int32_t id) {
    return objectIdToComponent.count(id) > 0;
  }
};
