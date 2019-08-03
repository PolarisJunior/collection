
#include "GameObject.h"

GameObject::~GameObject() {
  for (auto func : destroyFuncs) {
    func(uid);
  }
}