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
class ChunkIterator
    : public std::iterator<std::random_access_iterator_tag, Vector3<int32_t>> {
 public:
  int32_t width;
  int32_t length;
  int32_t height;

  int32_t idx = 0;
  ChunkIterator(int32_t i) : idx(i) {}
  ChunkIterator(int32_t w, int32_t l, int32_t h, int32_t i)
      : idx(i), width(w), height(h), length(l) {}

  bool operator<(const ChunkIterator& other) const {
    return this->idx < other.idx;
  };

  ChunkIterator& operator++() {
    idx++;
    return *this;
  }

  Vector3<int32_t> operator*() {
    // standard for n dimension is idx % dim1, (idx / dim1) % dim2
    // (idx / (dim1 * dim2)) % dim3...
    return Vector3<int32_t>(idx % width, (idx / width) % height,
                            idx / (width * length));
  }
};

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

  ChunkIterator begin() { return ChunkIterator(width, length, height, 0); }

  ChunkIterator end() { return ChunkIterator(width * length * height); }

 private:
  std::unordered_map<Vector3<int32_t>, Block::Type> blocksInChunk;
};
