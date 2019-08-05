
#include "GameObject.h"
#include <iostream>

GameObject::GameObject(GameObject&& other)
    : uid(std::move(other.uid)),
      transform_(std::move(other.transform_)),
      accessFuncs(std::move(other.accessFuncs)) {
  for (auto func : accessFuncs) {
    func(*this, OpType::MOVE);
  }
}

GameObject::~GameObject() {
  for (auto func : accessFuncs) {
    func(*this, OpType::DESTROY);
  }
}
