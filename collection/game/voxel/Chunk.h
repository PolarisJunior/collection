#pragma once
#include <cstdint>
#include <unordered_map>
#include "Block.h"
#include "math/Mathf.h"
#include "math/Vector3.h"

/*
  We define 0, 0, 0 of a chunk to be the bottommost, leftmost, backmost
  point of a chunk
 */

class Chunk {
 public:
  int32_t width = 16;
  int32_t length = 16;
  int32_t height = 16;

  int32_t x;
  int32_t y;
  int32_t z;

  void setBlockType(int32_t x, int32_t y, int32_t z, Block::Type type) {
    if (Mathf::inRange(x, 0, width) && Mathf::inRange(y, 0, height) &&
        Mathf::inRange(z, 0, length)) {
      blocksInChunk[Vector3<int32_t>(x, y, z)] = type;
    }
  }

  Block::Type getBlockType(int32_t x, int32_t y, int32_t z) {
    auto it = blocksInChunk.find(Vector3(x, y, z));
    if (it != blocksInChunk.end()) {
      return it->second;
    }
    return Block::Type::AIR;
  }

 private:
  std::unordered_map<Vector3<int32_t>, Block::Type> blocksInChunk;
};