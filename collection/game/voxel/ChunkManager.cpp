
#include "ChunkManager.h"
#include <math.h>
#include <algorithm>
#include <numeric>
#include "VoxelServiceLocator.h"
#include "math/Mathf.h"

#include <iostream>

ChunkManager::ChunkManager(ChunkMeshBuilder&& b)
    : terrainGenerator(VoxelServiceLocator::instance().terrainGenerator()),
      chunkRenders(),
      nearbyChunksMap(),
      builder(b) {}

bool ChunkManager::refreshLoadedChunks(float x, float y, float z) {
  for (int xPos = -chunkLoadRadius; xPos <= chunkLoadRadius; xPos++) {
    for (int zPos = -chunkLoadRadius; zPos <= chunkLoadRadius; zPos++) {
      // nearbyChunksMap[Vec3i(xPos, -1, zPos)] = Chunk(xPos, -1, zPos);
      nearbyChunksMap.insert(
          std::pair(Vec3i(xPos, -1, zPos), Chunk(xPos, -1, zPos)));
    }
  }

  for (auto& posChunkPair : nearbyChunksMap) {
    terrainGenerator.generateTerrain(posChunkPair.second);
  }

  return true;
}

void ChunkManager::moveCenter(const Vec3& newCenter) {
  // TODO add checks for big jumps
  Vec3i newCenterChunkPos = worldPositionToChunkPosition(newCenter);
  if (newCenterChunkPos != lastCenterPosition) {
    std::cout << newCenterChunkPos << " last" << lastCenterPosition << "\n";
    // Reference OneNote Programming/Iterating 2d Matrix
    Vec3i delta = newCenterChunkPos - lastCenterPosition;
    // if delta points left, chunks on right need to be unloaded and chunks on
    // left need to be loaded, same for vertical deltas
    Vec3i center = lastCenterPosition;
    Vec3i sgn =
        Vec3i(Mathf::sign(delta.x), Mathf::sign(delta.y), Mathf::sign(delta.z));

    Vec3i edge = center + sgn * chunkLoadRadius;
    Vec3i otherEdge = edge + delta;

    // Vec3i axes[] = {Vec3i(1, 0, 0), Vec3i(0, 0, 1)};
    // Vec3i orthoAxes[] = {Vec3i(0, 0, 1), Vec3i(1, 0, 0)};
    // int j = 0;
    // for (const Vec3i& axis : axes) {
    //   // zero out irrelevant axes
    //   for (Vec3i i = axis * otherEdge; i != edge * axis; i -= sgn * axis) {
    //     for (int32_t k = )
    //   }
    //   j++;
    // }
    // LOAD CHUNKS
    for (int i = otherEdge.x; i != edge.x; i -= sgn.x) {
      for (int32_t z = center.z - chunkLoadRadius;
           z <= center.z + chunkLoadRadius; z++) {
        loadChunk(Vec3i(i, -1, z));
      }
    }

    for (int i = otherEdge.z; i != edge.z; i -= sgn.z) {
      for (int32_t x = center.x - chunkLoadRadius;
           x <= center.x + chunkLoadRadius; x++) {
        loadChunk(Vec3i(x, -1, i));
      }
    }

    // UNLOAD CHUNKS
    edge = -(edge - center) + center;
    otherEdge = edge + delta;
    for (int i = edge.x; i != otherEdge.x; i += sgn.x) {
      for (int32_t z = center.z - chunkLoadRadius;
           z <= center.z + chunkLoadRadius; z++) {
        unloadChunk(Vec3i(i, -1, z));
      }
    }

    for (int i = edge.z; i != otherEdge.z; i += sgn.z) {
      for (int32_t x = center.x - chunkLoadRadius;
           x <= center.x + chunkLoadRadius; x++) {
        unloadChunk(Vec3i(x, -1, i));
      }
    }

    std::cout << "chunks left: " << nearbyChunksMap.size() << "\n";
    this->lastCenterPosition = newCenterChunkPos;
  }
}

void ChunkManager::buildRenders() {
  for (auto& posChunkPair : nearbyChunksMap) {
    Chunk& chunk = posChunkPair.second;
    chunkRenders.insert(std::pair(
        posChunkPair.first,
        RenderActor(builder.buildMesh(chunk), chunk.baseTransform())));
  }
}

void ChunkManager::renderChunks() {
  // std::cout << chunkRenders.size() << std::endl;
  for (auto& posRenderPair : chunkRenders) {
    posRenderPair.second.render();
  }
}

void ChunkManager::loadChunk(const Vec3i& chunkPos) {
  nearbyChunksMap[chunkPos] = Chunk(chunkPos.x, chunkPos.y, chunkPos.z);
  Chunk& chunk = nearbyChunksMap[chunkPos];
  terrainGenerator.generateTerrain(chunk);
  chunkRenders.insert(std::pair(
      chunkPos, RenderActor(builder.buildMesh(chunk), chunk.baseTransform())));
}

void ChunkManager::unloadChunk(const Vec3i& chunkPos) {
  nearbyChunksMap.erase(chunkPos);
  chunkRenders.erase(chunkPos);
}

Vec3i ChunkManager::worldPositionToChunkPosition(const Vec3& worldPos) const {
  Vec3i offsetForNegatives(worldPos.x < 0, worldPos.y < 0, worldPos.z < 0);
  return Vec3i(worldPos.x / chunkWidth, worldPos.y / chunkHeight,
               worldPos.z / chunkLength) -
         offsetForNegatives;
}
