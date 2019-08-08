
#include "ChunkMeshBuilder.h"
#include <algorithm>
#include <iostream>
#include "game/voxel/Block.h"
#include "game/voxel/BlockDatabase.h"
#include "graphics/TextureAtlas.h"
#include "graphics/models/PlaneMesh.h"
#include "graphics/util/MeshBuilder.h"
#include "math/Mat4.h"

using vec = Vector3<int32_t>;
std::vector<Vector3<int32_t>> allDirections = {vec::up(),      vec::down(),
                                               vec::right(),   vec::left(),
                                               vec::forward(), vec::backward()};

Mesh ChunkMeshBuilder::buildMesh(const Chunk& chunk) const {
  Mesh mesh;
  static Mesh faceMesh = PlaneMesh();

  MeshBuilder builder(
      faceMesh.vertices().size() * chunk.width * chunk.height * chunk.length,
      faceMesh.triangles().size() * chunk.width * chunk.height * chunk.length);

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

  // number of textures in both dimensions of the atlas
  const Vec2 numTextures = Vec2(atlas.numCols(), atlas.numRows());

  // Size of a pixel on the texture in UV space
  const float pixelWidth = 1.0 / atlas.width();
  const float pixelHeight = 1.0 / atlas.height();

  for (auto it = chunk.blocksInChunk.begin(); it != chunk.blocksInChunk.end();
       ++it) {
    // chunk space position
    const Vector3<int32_t> blockPos = it->first;

    // convert uncovered dirt to grass
    const Block::Type blockAbove = chunk.getBlockType(vec::up() + blockPos);

    const Block::Type blockType = blockAbove == Block::Type::AIR
                                      ? Block::Type::GRASS
                                      : chunk.getBlockType(blockPos);

    int32_t i = 0;
    for (const vec& direction : allDirections) {
      const vec adjacentPos = blockPos + direction;
      Block::Type adjacentBlockType = chunk.getBlockType(adjacentPos);

      if (adjacentBlockType == Block::Type::AIR) {
        Block::Face face = Block::indicesToFaces.at(i);
        int32_t blockIdx = BlockDatabase::getAtlasId(blockType, face);

        std::vector<Vec2> newUvs(faceMesh.uvs().size());

        // least magnitude corner of the subtexture
        const Vec2 uvOffset =
            Vec2((float)(blockIdx % atlas.numCols()) / atlas.numCols() +
                     pixelWidth / 2,
                 ((float)blockIdx / atlas.numCols()) / atlas.numRows() +
                     pixelHeight / 2);

        std::transform(
            faceMesh.uvs().begin(), faceMesh.uvs().end(), newUvs.begin(),
            [&numTextures, &uvOffset, pixelWidth, pixelHeight](const Vec2& st) {
              return st / numTextures + uvOffset +
                     Vec2(pixelWidth / 2 * (1 - st.x) - pixelWidth * st.x,
                          pixelHeight / 2 * (1 - st.y) - pixelHeight * st.y);
            });

        // Center and then reposition all sides are some
        // particular distance from the center point of a block
        builder.append(faces[i].vertices(), faces[i].triangles(),
                       std::move(newUvs), faces[i].normals(),
                       Vec3(blockPos.x + (float)direction.x / 2,
                            blockPos.y + 0.5 + (float)direction.y / 2,
                            blockPos.z + (float)direction.z / 2));
      }
      i++;
    }
  }

  return builder.build();
}