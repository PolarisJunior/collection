#pragma once
#include "graphics/models/Mesh.h"

class Transform;

// Contains a mesh that was sent to the GPU
class RenderUnit {
 public:
  RenderUnit(Mesh&& m);
  RenderUnit(RenderUnit&& u);
  ~RenderUnit();

  void render(Transform& transform);

  Mesh mesh;

 private:
  uint32_t vao = 0;
  std::vector<uint32_t> bufferIds;
};