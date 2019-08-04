#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include "GameObject.h"
#include "Transform.h"

class ComponentBase {};

// Uses CRTP to create the static map per template instance

template <typename Derived>
class Component : public ComponentBase {
  using RealComponent = Derived;

 public:
  Component() = default;
  Component(const Component& c) = delete;

  Component& operator=(const Component& other) = delete;
  Component& operator=(Component&& other) = delete;

  GameObject& gameObject() { return *gameObject_; }
  Transform& transform() { return gameObject().transform(); }

  // Called when the component is first built
  virtual void built(){};

 private:
  GameObject* gameObject_ = nullptr;

  inline static std::unordered_map<int64_t, RealComponent> objectIdToComponent;

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
    comp.built();
    return comp;
  }

  // Called by the owning game object when it is destructed
  static void destroyComponent(int64_t id) { objectIdToComponent.erase(id); }

  static void accessComponent(GameObject& go, GameObject::OpType op) {
    using Op = GameObject::OpType;
    switch (op) {
      case Op::DESTROY: {
        objectIdToComponent.erase(go.getInstanceId());
        break;
      }
      case Op::MOVE: {
        RealComponent& comp = objectIdToComponent[go.getInstanceId()];
        comp.gameObject_ = &go;
        break;
      }
    }
  }

  // Get the component associated with the gameobject
  static RealComponent& getComponent(int64_t id) {
    return objectIdToComponent.at(id);
  }

  // gameobject has component?
  static bool hasComponent(int64_t id) {
    return objectIdToComponent.count(id) > 0;
  }
};
