#pragma once

#include <cstdint>
#include <functional>
#include <vector>

class GameObject {
 public:
  GameObject() {
    uidCounter++;
    uid = uidCounter;
  }

  GameObject(const GameObject& other) = delete;
  ~GameObject();

  int32_t getInstanceId() const { return uid; }

  GameObject& operator=(const GameObject& other) = delete;

  template <typename T>
  T& addComponent() {
    destroyFuncs.push_back(T::destroyComponent);
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

 private:
  int32_t uid = 0;

  // Functions to call to destroy all the attached components
  std::vector<std::function<void(int32_t)>> destroyFuncs;

  inline static int32_t uidCounter = 0;
};