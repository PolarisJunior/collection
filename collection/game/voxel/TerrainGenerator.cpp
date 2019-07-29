#include "TerrainGenerator.h"

void TerrainGenerator::generateTerrain(Chunk& chunk,
                                       int32_t x,
                                       int32_t y,
                                       int32_t z) {
  for (auto it = chunk.begin(); it != chunk.end(); ++it) {
    Vector3<int32_t> p = *it;

    chunk.setBlockType(p, Block::Type::DIRT);
  }
}