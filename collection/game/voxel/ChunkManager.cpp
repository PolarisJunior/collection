
#include "ChunkManager.h"
#include <math.h>
#include <algorithm>
#include <numeric>
#include "VoxelServiceLocator.h"
#include "math/Mathf.h"

#include <iostream>

ChunkManager::ChunkManager()
    : terrainGenerator(VoxelServiceLocator::instance().terrainGenerator()),
      chunksInRange(
          std::vector(numChunksInRow(), std::vector<Chunk>(numChunksInRow()))),
      nearbyChunksMap() {}

bool ChunkManager::refreshLoadedChunks(float x, float y, float z) {
  for (int xPos = -chunkLoadRadius; xPos <= chunkLoadRadius; xPos++) {
    for (int zPos = -chunkLoadRadius; zPos <= chunkLoadRadius; zPos++) {
      // chunksInRange[xPos + chunkLoadRadius][zPos + chunkLoadRadius] =
      //     Chunk(xPos, -1, zPos);
      nearbyChunksMap[Vec3i(xPos, -1, zPos)] = Chunk(xPos, -1, zPos);
    }
  }

  for (auto& posChunkPair : nearbyChunksMap) {
    terrainGenerator.generateTerrain(posChunkPair.second);
    loadedChunks_.push_back(std::move(posChunkPair.second));
  }

  // for (auto& innerList : chunksInRange) {
  //   for (Chunk& chunk : innerList) {
  //     terrainGenerator.generateTerrain(chunk);
  //     loadedChunks_.push_back(std::move(chunk));
  //   }
  // }

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

    for (int i = otherEdge.x; i != edge.x; i -= sgn.x) {
      for (int32_t z = center.z - chunkLoadRadius;
           z <= center.z + chunkLoadRadius; z++) {
        std::cout << "Loading Chunks: " << Vec3i(i, -1, z) << std::endl;
      }
    }

    edge = -(edge - center) + center;
    otherEdge = edge + delta;
    for (int i = edge.x; i != otherEdge.x; i += sgn.x) {
      for (int32_t z = center.z - chunkLoadRadius;
           z <= center.z + chunkLoadRadius; z++) {
        std::cout << "Unloading Chunks: " << Vec3i(i, -1, z) << std::endl;
      }
    }

    std::cout << "chunks left: " << nearbyChunksMap.size() << "\n";
    this->lastCenterPosition = newCenterChunkPos;
  }
}

Vec3i ChunkManager::worldPositionToChunkPosition(const Vec3& worldPos) const {
  Vec3i offsetForNegatives(worldPos.x < 0, worldPos.y < 0, worldPos.z < 0);
  return Vec3i(worldPos.x / chunkWidth, worldPos.y / chunkHeight,
               worldPos.z / chunkLength) -
         offsetForNegatives;
}

std::vector<Chunk>& ChunkManager::loadedChunks() {
  return loadedChunks_;
}