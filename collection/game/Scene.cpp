
#include "Scene.h"

Scene* Scene::mainScene_ = nullptr;

GameObject& Scene::addGameObject() {
  gameObjects.emplace_back(GameObject());
  return gameObjects.back();
}

void Scene::mainScene(Scene& sc) {
  mainScene_ = &sc;
}

Scene& Scene::mainScene() {
  return *mainScene_;
}
