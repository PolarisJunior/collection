
#pragma once

#include <vector>
#include "game/ecs/Transform.h"
#include "math/Mat4.h"
#include "math/Vector2.h"
#include "math/Vector3.h"

/* A modifiable mesh */
class Mesh {
 public:
  Mesh() = default;
  Mesh(const Mesh& other) = default;
  Mesh(Mesh&& other)
      : vertices_(std::move(other.vertices_)),
        triangles_(std::move(other.triangles_)),
        uvs_(std::move(other.uvs_)),
        normals_(std::move(other.normals_)) {}

  Mesh(const std::vector<Vec3>& verts,
       const std::vector<int32_t>& tris,
       const std::vector<Vec2>& uvs,
       const std::vector<Vec3>& norms)
      : vertices_(verts), triangles_(tris), uvs_(uvs), normals_(norms) {}

  Mesh(std::vector<Vec3>&& verts,
       std::vector<int32_t>&& tris,
       std::vector<Vec2>&& uvs,
       std::vector<Vec3>&& norms)
      : vertices_(std::move(verts)),
        triangles_(std::move(tris)),
        uvs_(std::move(uvs)),
        normals_(std::move(norms)) {}

  Mesh& operator=(Mesh&& other) {
    this->vertices_ = std::move(other.vertices_);
    this->triangles_ = std::move(other.triangles_);
    this->uvs_ = std::move(other.uvs_);
    this->normals_ = std::move(other.normals_);
    return *this;
  }

  void setVertices(const std::vector<Vec3>& vs) { vertices_ = vs; }
  void setTriangles(const std::vector<int32_t>& ts) { triangles_ = ts; }
  void setUvs(const std::vector<Vec2>& uvs) { uvs_ = uvs; }
  void setNormals(const std::vector<Vec3>& norms) { normals_ = norms; }

  void uvs(std::vector<Vec2>&& uvs) { uvs_ = std::move(uvs); }

  // Join two meshes together with an offset and rotation
  void joinMesh(const Mesh& otherMesh,
                const Quaternion& rotation,
                float offsetX = 0,
                float offsetY = 0,
                float offsetZ = 0);
  void joinMesh(const Mesh& otherMesh, const Transform& t);
  void joinMesh(const Mesh& otherMesh,
                float offsetX = 0,
                float offsetY = 0,
                float offsetZ = 0);

  void translateVertices(const Vec3& v);
  void translateVertices(float x, float y, float z);

  void rotateVertices(const Quaternion& rotation);
  void rotateVertices(const Mat4& rotationMatrix);

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