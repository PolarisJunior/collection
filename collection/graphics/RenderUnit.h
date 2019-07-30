#pragma once
#include "graphics/models/Mesh.h"

class Transform;

// Contains a mesh that was sent to the GPU
class RenderUnit {
 public:
  RenderUnit(Mesh&& m);

  void render(Transform& transform);

  Mesh mesh;
  uint32_t vao = 0;
};