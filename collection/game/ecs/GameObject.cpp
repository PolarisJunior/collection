
#include "GameObject.h"

GameObject::GameObject(GameObject&& other)
    : uid(other.uid),
      transform_(std::move(other.transform_)),
      accessFuncs(other.accessFuncs) {
  for (auto func : other.accessFuncs) {
    func(*this, OpType::MOVE);
  }
  other.uid = 0;
}

GameObject::~GameObject() {
  for (auto func : accessFuncs) {
    func(*this, OpType::DESTROY);
  }
}
