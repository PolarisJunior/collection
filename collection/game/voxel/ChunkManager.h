#pragma once

#include "Chunk.h"
#include "TerrainGenerator.h"
#include "math/Vector3.h"

class ChunkManager {
 public:
  ChunkManager();
  // refresh which chunks are loaded based on world position, returns true if
  // any changes were made
  bool refreshLoadedChunks(const Vec3& pos) {
    return refreshLoadedChunks(pos.x, pos.y, pos.z);
  }
  bool refreshLoadedChunks(float x, float y, float z);

  std::vector<Chunk>& loadedChunks();

  TerrainGenerator& terrainGenerator;

  const uint32_t chunkWidth = 16;
  const uint32_t chunkHeight = 16;
  const uint32_t chunkLength = 16;

 private:
  std::vector<Chunk> loadedChunks_;
};