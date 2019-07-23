
#pragma once

#include <vector>
#include "math/Vector2.h"
#include "math/Vector3.h"

class Mesh {
 public:
  Mesh() = default;
  Mesh(const std::vector<Vec3>& verts,
       const std::vector<int32_t>& tris,
       const std::vector<Vec2>& uvs,
       const std::vector<Vec3>& norms)
      : vertices_(verts), triangles_(tris), uvs_(uvs), normals_(norms) {}

  void setVertices(const std::vector<Vec3>& vs) { vertices_ = vs; }
  void setTriangles(const std::vector<int32_t>& ts) { triangles_ = ts; }

  void setUvs(const std::vector<Vec2>& uvs) { uvs_ = uvs; }
  void setNormals(const std::vector<Vec3>& norms) { normals_ = norms; }

  const std::vector<Vec3>& vertices() const { return vertices_; };
  const std::vector<int32_t>& triangles() const { return triangles_; };
  const std::vector<Vec3>& normals() const { return normals_; };
  const std::vector<Vec2>& uvs() const { return uvs_; };

 private:
  std::vector<Vec3> vertices_;
  std::vector<int32_t> triangles_;

  std::vector<Vec3> normals_;
  std::vector<Vec2> uvs_;
  // indices for triangles
};