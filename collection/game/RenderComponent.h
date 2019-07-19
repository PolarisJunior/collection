
#pragma once

#include "Component.h"

class Actor;
/* Render, requires a sprite component */
class RenderComponent : public Component {
 public:
  /* Renders the attached actor */
  void render(float interpolation);

  void onAttached(Actor* actor) override;
};