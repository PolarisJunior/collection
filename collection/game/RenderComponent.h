
#pragma once

#include "Component.h"

/* Render, requires a sprite component */
class RenderComponent : public Component {
 public:
  const int32_t componentId = ComponentId::RENDERABLE;

  void render(float interpolation);

  void onAttached(Actor* actor) override;
};