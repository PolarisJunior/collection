
#include "ChunkMeshBuilder.h"
#include <algorithm>
#include <iostream>
#include "game/voxel/Block.h"
#include "game/voxel/BlockDatabase.h"
#include "graphics/TextureAtlas.h"
#include "graphics/models/PlaneMesh.h"
#include "math/Mat4.h"

using vec = Vector3<int32_t>;
std::vector<Vector3<int32_t>> allDirections = {vec::up(),      vec::down(),
                                               vec::right(),   vec::left(),
                                               vec::forward(), vec::backward()};

Mesh ChunkMeshBuilder::buildMesh(const Chunk& chunk) const {
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
    Block::Type blockType = it->second;

    // convert uncovered dirt to grass
    Block::Type blockAbove = chunk.getBlockType(vec::up() + blockPos);
    if (blockAbove == Block::Type::AIR) {
      blockType = Block::Type::GRASS;
    }

    int32_t i = 0;
    for (const vec& direction : allDirections) {
      const vec adjacentPos = blockPos + direction;
      Block::Type adjacentBlockType = chunk.getBlockType(adjacentPos);

      if (adjacentBlockType == Block::Type::AIR) {
        Block::Face face = Block::indicesToFaces.at(i);
        // int32_t blockIdx = atlas.textureIndex(3, 1);
        // int32_t blockIdx = Block::getAtlasIndex(adjacentBlockType, face);
        int32_t blockIdx = BlockDatabase::getAtlasId(blockType, face);
        std::vector<Vec2> newUvs;

        float pixelWidth = 1.0 / atlas.width();
        float pixelHeight = 1.0 / atlas.height();

        const Vec2 uvOffset =
            Vec2((float)(blockIdx % atlas.numCols()) / atlas.numCols() +
                     pixelWidth / 2,
                 (float)(blockIdx / atlas.numRows()) / atlas.numRows() +
                     pixelHeight / 2);

        const Vec2 numTextures = Vec2(atlas.numCols(), atlas.numRows());

        std::transform(
            faceMesh.uvs().begin(), faceMesh.uvs().end(),
            std::back_inserter(newUvs),
            [&numTextures, &uvOffset, pixelWidth, pixelHeight](const Vec2& st) {
              return st / numTextures + uvOffset +
                     Vec2(pixelWidth / 2 * (1 - st.x) - pixelWidth * st.x,
                          pixelHeight / 2 * (1 - st.y) - pixelHeight * st.y);
            });

        faces[i].uvs(std::move(newUvs));

        // faces[i].uvs()) Center and then reposition all sides are some
        // particular distance from the center point of a block
        mesh.joinMesh(faces[i], blockPos.x + (float)direction.x / 2,
                      blockPos.y + 0.5 + (float)direction.y / 2,
                      blockPos.z + (float)direction.z / 2);
      }
      i++;
    }
  }
  return mesh;
}