
#include "ChunkManager.h"
#include "VoxelServiceLocator.h"

ChunkManager::ChunkManager()
    : terrainGenerator(VoxelServiceLocator::instance().terrainGenerator()) {}

bool ChunkManager::refreshLoadedChunks(float x, float y, float z) {
  for (int xPos = -3; xPos <= 3; xPos++) {
    for (int zPos = -3; zPos <= 3; zPos++) {
      loadedChunks_.push_back(Chunk(xPos, -1, zPos));
    }
  }

  for (Chunk& chunk : loadedChunks_) {
    terrainGenerator.generateTerrain(chunk);
  }
  return true;
}

std::vector<Chunk>& ChunkManager::loadedChunks() {
  return loadedChunks_;
}