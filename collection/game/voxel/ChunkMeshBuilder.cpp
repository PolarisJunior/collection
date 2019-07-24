
#include "ChunkMeshBuilder.h"
#include <iostream>
#include "graphics/models/CubeMesh.h"
#include "graphics/models/PlaneMesh.h"
#include "math/Mat4.h"

/*
dynamic programming solution?
build array 16 * 16 * 16 true if occupied

 */

std::vector<Vector3<int32_t>> getAdjacentPoints(const Vector3<int32_t>& v) {
  std::vector<Vector3<int32_t>> points;
  using vec = Vector3<int32_t>;

  points.push_back(v + vec::up());
  points.push_back(v + vec::down());
  points.push_back(v + vec::right());
  points.push_back(v + vec::left());
  points.push_back(v + vec::forward());
  points.push_back(v + vec::backward());
  return points;
}

Mesh ChunkMeshBuilder::buildMesh(const Chunk& c) {
  Mesh mesh;
  for (auto it = c.blocksInChunk.begin(); it != c.blocksInChunk.end(); ++it) {
    const Vector3<int32_t> pos = it->first;
    const Block::Type type = it->second;

    auto points = getAdjacentPoints(pos);
    for (auto pIt = points.begin(); pIt != points.end(); ++pIt) {
      if (c.getBlockType(*pIt) == Block::Type::AIR) {
        Mesh m = CubeMesh();
        m.translateVertices(pos.x, pos.y, pos.z);
        mesh.joinMesh(m);
        // std::cout << "mesh joined: " << pos << std::endl;
        break;
      }
    }
  }
  return mesh;
}