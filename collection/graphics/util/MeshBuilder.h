#pragma once

#include "graphics/models/Mesh.h"

/*
Swiftly constructs a mesh out of several meshes
 */
class MeshBuilder {
 public:
  MeshBuilder(int32_t numVerts, int32_t numIndices);

  void append(const std::vector<Vec3>& verts,
              const std::vector<int32_t>& tris,
              const std::vector<Vec2>&& texCoords,
              const std::vector<Vec3>& norms,
              const Vec3& translation);

  Mesh build();

  std::vector<Vec3> vertices;
  std::vector<int32_t> indices;
  std::vector<Vec2> uvs;
  std::vector<Vec3> normals;

  int32_t vertsAdded = 0;
  int32_t indicesAdded = 0;
};