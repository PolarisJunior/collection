#pragma once

#include <algorithm>
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
  Component& operator=(const Component& other) = delete;
  Component& operator=(Component&& other) = delete;

  GameObject& gameObject() { return *gameObject_; }
  Transform& transform() { return gameObject().transform(); }

  // Copies the component except for its attached gameobject
  RealComponent copy() {
    return RealComponent(*dynamic_cast<RealComponent*>(this));
  }

  // Called when the component is first built
  virtual void built(){};

  // might be possible to optimize this
  inline static std::vector<RealComponent*> all() {
    std::vector<RealComponent*> out =
        std::vector<RealComponent*>(objectIdToComponent.size());
    std::transform(objectIdToComponent.begin(), objectIdToComponent.end(),
                   out.begin(),
                   [](auto& idCompPair) { return &idCompPair.second; });
    return out;
  }

 protected:
  Component() = default;
  Component(const Component& c) : gameObject_(nullptr) {}

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
  // static void destroyComponent(int64_t id) { objectIdToComponent.erase(id); }

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
