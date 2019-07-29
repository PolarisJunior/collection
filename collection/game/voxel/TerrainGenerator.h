#pragma once

#include "Chunk.h"
#include "math/Vector3.h"

class TerrainGenerator {
 public:
  // Fills a chunk with blocks based on the chunk-space position
  void generateTerrain(Chunk& chunk) {
    generateTerrain(chunk, chunk.x, chunk.y, chunk.z);
  }
  void generateTerrain(Chunk& chunk, int32_t x, int32_t y, int32_t z);
};