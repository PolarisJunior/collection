
#include "ChunkMeshBuilder.h"
#include <iostream>
#include "graphics/models/CubeMesh.h"
#include "graphics/models/PlaneMesh.h"
#include "graphics/models/QuadMesh.h"
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

using vec = Vector3<int32_t>;
std::vector<Vector3<int32_t>> allDirections = {vec::up(),      vec::down(),
                                               vec::right(),   vec::left(),
                                               vec::forward(), vec::backward()};

Mesh ChunkMeshBuilder::buildMesh(const Chunk& chunk) {
  Mesh mesh;
  Mesh faceMesh = PlaneMesh();

  std::vector<Mesh> faces;
  std::fill_n(std::back_inserter(faces), 6, faceMesh);

  // faces are with respect to us being -x, -y, -z of the chunk.
  Mesh& topFace = faces[0];
  Mesh& bottomFace = faces[1];
  bottomFace.rotateVertices(Quaternion(Mathf::pi, Vec3::forward()));

  Mesh& rightFace = faces[2];
  Mesh& leftFace = faces[3];
  rightFace.rotateVertices(Quaternion(-Mathf::pi_2, Vec3::right()) *
                           Quaternion(-Mathf::pi_2, Vec3::forward()));
  leftFace.rotateVertices(Quaternion(-Mathf::pi_2, Vec3::right()) *
                          Quaternion(Mathf::pi_2, Vec3::forward()));

  Mesh& backFace = faces[4];
  Mesh& frontFace = faces[5];
  frontFace.rotateVertices(Quaternion(-Mathf::pi_2, Vec3::right()));
  backFace.rotateVertices(Quaternion(Mathf::pi, Vec3::up()) *
                          Quaternion(-Mathf::pi_2, Vec3::right()));

  for (auto it = chunk.blocksInChunk.begin(); it != chunk.blocksInChunk.end();
       ++it) {
    const Vector3<int32_t> blockPos = it->first;
    const Block::Type blockType = it->second;

    int32_t i = 0;
    for (const vec& direction : allDirections) {
      const vec adjacentPos = blockPos + direction;
      if (chunk.getBlockType(adjacentPos) == Block::Type::AIR) {
        // Center and then reposition
        // all sides are some particular distance from the center point of a
        // block
        mesh.joinMesh(faces[i], blockPos.x + (float)direction.x / 2,
                      blockPos.y + 0.5 + (float)direction.y / 2,
                      blockPos.z + (float)direction.z / 2);
      }
      i++;
    }
  }
  return mesh;
}