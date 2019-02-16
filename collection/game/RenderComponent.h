
#pragma once

#include "Component.h"

class Actor;
/* Render, requires a sprite component */
class RenderComponent : public Component {
 public:
  void render(float interpolation);

  void onAttached(Actor* actor) override;
};