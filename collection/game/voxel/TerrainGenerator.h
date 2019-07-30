#pragma once

#include <unordered_map>
#include "Chunk.h"
#include "math/Vector2.h"
#include "math/Vector3.h"

class TerrainGenerator {
 public:
  // Fills a chunk with blocks based on the chunk-space position
  void generateTerrain(Chunk& chunk) {
    generateTerrain(chunk, chunk.x, chunk.y, chunk.z);
  }
  void generateTerrain(Chunk& chunk, int32_t x, int32_t y, int32_t z);

  // temporary, min height for block, should make this more versatile later
  int32_t minHeight = 2;

 private:
  //  Generates a height map based on a chunk space position
  std::unordered_map<Vector2<int32_t>, int32_t> generateHeightMap(
      const Chunk& chunk);
};
