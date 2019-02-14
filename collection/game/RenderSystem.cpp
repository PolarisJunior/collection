
#include "RenderSystem.h"
#include "RenderComponent.h"

RenderSystem renderSystem;

void RenderSystem::registerComponent(RenderComponent* comp) {
  registered.push_back(comp);
}

void RenderSystem::renderAll(float interp) {
  for (auto it = registered.begin(); it < registered.end(); it++) {
    (*it)->render(interp);
  }
}
