
#pragma once

#include "math/Vector2.h"
#include "math/Vector3.h"

class Mesh {
 public:
  void setVertices(Vec3* vs) { vertices_ = vs; }
  void setTriangles(int32_t* ts) { triangles_ = ts; }

  Vec3* vertices_;
  Vec3* normals_;
  Vec2* uvs_;
  // indices for triangles
  int32_t* triangles_;
};