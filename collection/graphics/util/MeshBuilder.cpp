#include "MeshBuilder.h"
#include <algorithm>
#include <iostream>

MeshBuilder::MeshBuilder(int32_t numVertices, int32_t numIndices)
    : vertices(numVertices),
      indices(numIndices),
      uvs(numVertices),
      normals(numVertices) {}

Mesh MeshBuilder::build() {
  vertsAdded = 0;
  indicesAdded = 0;
  return Mesh(vertices, indices, uvs, normals);
}

void MeshBuilder::append(const std::vector<Vec3>& verts,
                         const std::vector<int32_t>& tris,
                         const std::vector<Vec2>&& texCoords,
                         const std::vector<Vec3>& norms,
                         const Vec3& translation) {
  int32_t numVertsToAdd = verts.size();
  int32_t numIndicesToAdd = tris.size();

  std::transform(
      verts.begin(), verts.end(), vertices.begin() + vertsAdded,
      [&translation](const Vec3& p) -> Vec3 { return p + translation; });

  std::transform(tris.begin(), tris.end(), indices.begin() + indicesAdded,
                 [this](int32_t idx) { return idx + vertsAdded; });

  std::copy(texCoords.begin(), texCoords.end(), uvs.begin() + vertsAdded);
  std::copy(norms.begin(), norms.end(), normals.begin() + vertsAdded);

  vertsAdded += numVertsToAdd;
  indicesAdded += numIndicesToAdd;
}