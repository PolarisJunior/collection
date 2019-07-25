
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

Mesh ChunkMeshBuilder::buildMesh(const Chunk& c) {
  Mesh mesh;
  Mesh faceMesh = PlaneMesh();

  // faces are with respect to us being -x, -y, -z of the chunk.
  Mesh topFace = faceMesh;
  Mesh bottomFace = faceMesh;
  bottomFace.rotateVertices(Quaternion(Mathf::pi, Vec3::forward()));

  Mesh rightFace = faceMesh;
  Mesh leftFace = faceMesh;
  rightFace.rotateVertices(Quaternion(-Mathf::pi_2, Vec3::right()) *
                           Quaternion(-Mathf::pi_2, Vec3::forward()));
  leftFace.rotateVertices(Quaternion(-Mathf::pi_2, Vec3::right()) *
                          Quaternion(Mathf::pi_2, Vec3::forward()));

  Mesh backFace = faceMesh;
  Mesh frontFace = faceMesh;
  backFace.rotateVertices(Quaternion(Mathf::pi, Vec3::up()) *
                          Quaternion(-Mathf::pi_2, Vec3::right()));
  frontFace.rotateVertices(Quaternion(-Mathf::pi_2, Vec3::right()));

  for (auto it = c.blocksInChunk.begin(); it != c.blocksInChunk.end(); ++it) {
    const Vector3<int32_t> pos = it->first;
    const Block::Type type = it->second;

    auto points = getAdjacentPoints(pos);
    for (auto pIt = points.begin(); pIt != points.end(); ++pIt) {
      if (c.getBlockType(*pIt) == Block::Type::AIR) {
        Mesh m;
        // top and bottom faces
        mesh.joinMesh(topFace, pos.x, pos.y + 1, pos.z);
        mesh.joinMesh(bottomFace, pos.x, pos.y, pos.z);

        // front and back faces
        mesh.joinMesh(backFace, pos.x, pos.y + .5, pos.z + .5);
        mesh.joinMesh(frontFace, pos.x, pos.y + .5, pos.z - .5);

        // right and Left faces
        mesh.joinMesh(rightFace, pos.x + .5, pos.y + .5, pos.z);
        mesh.joinMesh(leftFace, pos.x - .5, pos.y + .5, pos.z);
        break;
      }
    }
  }
  return mesh;
}