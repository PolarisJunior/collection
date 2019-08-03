#pragma once

#include <cstdint>

class GameObject {
 public:
  GameObject() {
    uidCounter++;
    uid = uidCounter;
  }

  template <typename T>
  T& addComponent() {
    return T::addComponent(uid);
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
  inline static int32_t uidCounter = 0;
};