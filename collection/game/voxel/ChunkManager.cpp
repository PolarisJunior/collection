
#include "ChunkManager.h"
#include "VoxelServiceLocator.h"

ChunkManager::ChunkManager()
    : terrainGenerator(VoxelServiceLocator::instance().terrainGenerator()) {}

bool ChunkManager::refreshLoadedChunks(float x, float y, float z) {
  loadedChunks_.push_back(Chunk(0, -1, 0));
  loadedChunks_.push_back(Chunk(-1, -1, 0));
  loadedChunks_.push_back(Chunk(0, -1, 1));
  loadedChunks_.push_back(Chunk(-1, -1, 1));

  for (Chunk& chunk : loadedChunks_) {
    terrainGenerator.generateTerrain(chunk);
  }
  return true;
}

std::vector<Chunk>& ChunkManager::loadedChunks() {
  return loadedChunks_;
}