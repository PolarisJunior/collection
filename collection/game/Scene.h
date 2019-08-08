#pragma once

#include <list>
#include <vector>
#include "game/ecs/GameObject.h"

class Scene {
 public:
  Scene() = default;

  // std::vector<GameObject>& getRootGameObjects() {
  //   return std::vector<GameObject>(gameObjects.begin(), gameObjects.end());
  // }

  GameObject& addGameObject();

  static void mainScene(Scene& sc);
  static Scene& mainScene();

 private:
  std::list<GameObject> gameObjects;

  static Scene* mainScene_;
};
