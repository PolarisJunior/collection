
#include "graphics/models/Mesh.h"

#include <algorithm>
#include "util/Macros.h"

void Mesh::joinMesh(const Mesh& otherMesh,
                    const Quaternion& rotation,
                    float x,
                    float y,
                    float z) {
  int32_t dist = std::distance(vertices_.begin(), vertices_.end());

  Mat4 rotationMatrix = rotation.toMatrix();
  // add all vertices
  std::transform(otherMesh.vertices().begin(), otherMesh.vertices().end(),
                 std::back_inserter(vertices_),
                 [x, y, z, &rotationMatrix](const Vec3& p) -> Vec3 {
                   return (rotationMatrix * p) + Vec3(x, y, z);
                 });

  std::transform(otherMesh.triangles().begin(), otherMesh.triangles().end(),
                 std::back_inserter(triangles_),
                 [dist](int32_t idx) { return idx + dist; });

  uvs_.insert(uvs_.end(), otherMesh.uvs().begin(), otherMesh.uvs().end());
  // std::transform(
  //     otherMesh.uvs().begin(), otherMesh.uvs().end(),
  //     std::back_inserter(uvs_),
  //     [](const Vec2& st) { return st / 16.f + Vec2(1.0f / 16.f * 3, 0); });

  normals_.insert(normals_.end(), otherMesh.normals().begin(),
                  otherMesh.normals().end());
}

void Mesh::joinMesh(const Mesh& otherMesh, float x, float y, float z) {
  int32_t dist = std::distance(vertices_.begin(), vertices_.end());

  // add all vertices
  std::transform(
      otherMesh.vertices().begin(), otherMesh.vertices().end(),
      std::back_inserter(vertices_),
      [x, y, z](const Vec3& p) -> Vec3 { return p + Vec3(x, y, z); });

  std::transform(otherMesh.triangles().begin(), otherMesh.triangles().end(),
                 std::back_inserter(triangles_),
                 [dist](int32_t idx) { return idx + dist; });

  uvs_.insert(uvs_.end(), otherMesh.uvs().begin(), otherMesh.uvs().end());
  // std::transform(
  //     otherMesh.uvs().begin(), otherMesh.uvs().end(),
  //     std::back_inserter(uvs_),
  //     [](const Vec2& st) { return st / 16.f + Vec2(1.0f / 16.f * 3, 0); });

  normals_.insert(normals_.end(), otherMesh.normals().begin(),
                  otherMesh.normals().end());
}

void Mesh::joinMesh(const Mesh& otherMesh, const Transform& t) {}

void Mesh::translateVertices(const Vec3& v) {
  foreach (it, vertices_) { *it += v; }
}

void Mesh::translateVertices(float x, float y, float z) {
  translateVertices(Vec3(x, y, z));
}

void Mesh::rotateVertices(const Quaternion& rotation) {
  rotateVertices(rotation.toMatrix());
}

void Mesh::rotateVertices(const Mat4& rotationMatrix) {
  auto f = [&rotationMatrix](const Vec3& vec) { return rotationMatrix * vec; };

  std::transform(vertices_.begin(), vertices_.end(), vertices_.begin(), f);
  std::transform(normals_.begin(), normals_.end(), normals_.begin(), f);
}
