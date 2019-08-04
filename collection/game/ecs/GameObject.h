#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "Transform.h"

class GameObject {
 public:
  GameObject() {
    uidCounter++;
    uid = uidCounter;
  }

  GameObject(GameObject&& other);
  // copy constructor would require copying components
  GameObject(const GameObject& other) = delete;
  ~GameObject();

  int64_t getInstanceId() const { return uid; }

  Transform& transform() { return transform_; }

  GameObject& operator=(const GameObject& other) = delete;

  template <typename T>
  T& addComponent() {
    accessFuncs.push_back(T::accessComponent);
    return T::addComponent(*this);
  }

  template <typename T>
  T& getComponent() {
    return T::getComponent(uid);
  }

  template <typename T>
  bool hasComponent() {
    return T::hasComponent(uid);
  }

  enum class OpType { DESTROY, MOVE };

 private:
  int64_t uid = 0;
  Transform transform_{};

  // Functions to call to access instances of components
  std::vector<std::function<void(GameObject&, OpType)>> accessFuncs;

  inline static int64_t uidCounter = 0;
};
