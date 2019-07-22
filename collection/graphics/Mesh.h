
#pragma once

#include <vector>
#include "math/Vector2.h"
#include "math/Vector3.h"

class Mesh {
 public:
  void setVertices(const std::vector<Vec3>& vs) { vertices_ = vs; }
  void setTriangles(const std::vector<int32_t>& ts) { triangles_ = ts; }
  void setUvs(const std::vector<Vec2>& uvs) { uvs_ = uvs; }

  std::vector<Vec3> vertices_;
  std::vector<Vec3> normals_;
  std::vector<Vec2> uvs_;
  // indices for triangles
  std::vector<int32_t> triangles_;
};