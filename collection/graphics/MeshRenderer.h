#pragma once

#include "game/ecs/Component.h"
#include "graphics/RenderUnit.h"
#include "graphics/models/Mesh.h"

class MeshRenderer : public Component<MeshRenderer> {
 public:
  void mesh(Mesh&& m) { renderUnit = RenderUnit(std::move(m)); }

  void render() { renderUnit.render(transform()); }

 private:
  RenderUnit renderUnit;
};
