
#pragma once

#include <vector>

class RenderComponent;

class RenderSystem {
 public:
  void registerComponent(RenderComponent* comp);
  void unRegisterComponent(RenderComponent* comp);

  void renderAll(float interp);

 private:
  std::vector<RenderComponent*> registered;
};

extern RenderSystem renderSystem;