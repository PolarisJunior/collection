#pragma once
#include "RenderUnit.h"

// A render unit with transform information
class RenderActor {
 public:
  RenderActor(RenderUnit&& unit, const Transform& t);
  RenderActor(Mesh&& mesh, const Transform& t);

  void render();

  //  private:
  RenderUnit renderUnit;
  Transform transform;
};