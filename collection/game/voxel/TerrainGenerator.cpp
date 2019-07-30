#include "TerrainGenerator.h"
#include "math/Random.h"
#include "math/SimplexNoise.h"

#ifdef DEBUG
#include <iostream>
#endif

void TerrainGenerator::generateTerrain(Chunk& chunk,
                                       int32_t x,
                                       int32_t y,
                                       int32_t z) {
  auto heightMap = generateHeightMap(chunk);

  for (auto it = chunk.begin(); it != chunk.end(); ++it) {
    Vector3<int32_t> p = *it;
    if (p.y < heightMap[Vector2(p.x, p.z)]) {
      chunk.setBlockType(p, Block::Type::DIRT);
    }
  }
}

std::unordered_map<Vector2<int32_t>, int32_t>
TerrainGenerator::generateHeightMap(const Chunk& chunk) {
  double seed = Random::range(0.f, 10000.f);
  std::unordered_map<Vector2<int32_t>, int32_t> map;
  for (int32_t x = 0; x < chunk.width; ++x) {
    for (int32_t z = 0; z < chunk.length; ++z) {
      int32_t y = minHeight;
      // shift to range [0, 8]
      int32_t offset =
          7 * (SimplexNoise::noise((double)x * .05, (double)z * .05, seed) + 1);
      y += offset;
      map[Vector2<int32_t>(x, z)] = y;
    }
  }
  return map;
}