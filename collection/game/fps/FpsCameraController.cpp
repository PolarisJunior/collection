
#include "FpsCameraController.h"
#include <iostream>
#include "game/Camera.h"
#include "game/Scene.h"
#include "graphics/MeshRenderer.h"
#include "graphics/models/SphereMesh.h"
#include "physics/SphereCollider.h"
#include "ui/Input.h"
#include "ui/Mouse.h"

void FpsCameraController::update(float deltaTime) {
  if (Mouse::buttonDown(0)) {
    std::cout << "foo" << std::endl;
    Camera& mainCamera = Camera::getMainCamera();

    Ray ray = mainCamera.screenPointToRay(Mouse::pos().x, Mouse::pos().y);
    std::vector<SphereCollider*> colliders = SphereCollider::all();
    for (auto col : colliders) {
      std::cout << col->intersects(ray) << std::endl;
    }

    Scene& scene = Scene::mainScene();
    GameObject& go = scene.addGameObject();
    MeshRenderer& renderer = go.addComponent<MeshRenderer>();
    renderer.mesh(SphereMesh());
    go.transform().translate(ray.origin() + ray.direction() * 10);
  }
  // Input::g
}