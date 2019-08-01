#pragma once

#include "Chunk.h"
#include "TerrainGenerator.h"
#include "math/Vector3.h"

#include <unordered_map>

class ChunkManager {
 public:
  ChunkManager();
  // refresh which chunks are loaded based on world position, returns true if
  // any changes were made
  bool refreshLoadedChunks(const Vec3& pos) {
    return refreshLoadedChunks(pos.x, pos.y, pos.z);
  }
  bool refreshLoadedChunks(float x, float y, float z);

  // moves the world position center of loaded chunks
  void moveCenter(const Vec3& newCenter);

  int32_t numChunksInRange() const {
    int32_t w = numChunksInRow();
    return w * w;
  }

  int32_t numChunksInRow() const { return chunkLoadRadius * 2 + 1; }

  Vec3i worldPositionToChunkPosition(const Vec3& worldPos) const;

  std::vector<Chunk>& loadedChunks();

  TerrainGenerator& terrainGenerator;

  const uint32_t chunkWidth = 16;
  const uint32_t chunkHeight = 16;
  const uint32_t chunkLength = 16;

  // we load chunks in a square around the player of width  r*2+1
  const int32_t chunkLoadRadius = 3;

 private:
  std::vector<Chunk> loadedChunks_;
  // chunkspace but centered around the player
  std::vector<std::vector<Chunk>> chunksInRange;

  // chunkspace position
  std::unordered_map<Vec3i, Chunk> nearbyChunksMap;

  // Last chunk that was the center chunk
  Vec3i lastCenterPosition = Vec3i(0, 0, 0);
};