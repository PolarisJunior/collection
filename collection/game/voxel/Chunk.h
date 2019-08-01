#pragma once
#include <cstdint>
#include <unordered_map>
#include "Block.h"
#include "game/ecs/Transform.h"
#include "math/Mathf.h"
#include "math/Vector3.h"

#ifdef DEBUG
#include <iostream>
#endif

class ChunkIterator;

class Chunk {
  using Type = Block::Type;

 public:
  uint32_t width = 16;
  uint32_t length = 16;
  uint32_t height = 16;

  // Chunk space position of the chunk
  int32_t x = 0;
  int32_t y = 0;
  int32_t z = 0;

  Type defaultBlockType = Type::AIR;

  Chunk() = default;
  Chunk(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {
#ifdef DEBUG
    std::cout << "Chunk created at: " << Vector3<int32_t>(x, y, z) << std::endl;
#endif
  }

  void setBlockType(int32_t x, int32_t y, int32_t z, Block::Type type) {
    if (Mathf::inRange(x, 0, width) && Mathf::inRange(y, 0, height) &&
        Mathf::inRange(z, 0, length)) {
      blocksInChunk[Vector3<int32_t>(x, y, z)] = type;
    }
  }

  void setBlockType(const Vector3<int32_t>& pos, Block::Type type) {
    setBlockType(pos.x, pos.y, pos.z, type);
  }

  Type getBlockType(const Vector3<int32_t>& p) const {
    return getBlockType(p.x, p.y, p.z);
  }

  Type getBlockType(int32_t x, int32_t y, int32_t z) const {
    auto it = blocksInChunk.find(Vector3(x, y, z));
    if (it != blocksInChunk.end()) {
      return it->second;
    }
    return defaultBlockType;
  }

  Vec3 worldPosition() const {
    return Vec3((float)width * x, (float)height * y, (float)length * z);
  }

  // transform representing the base transform without any additional transforms
  Transform baseTransform() const { return Transform(worldPosition()); }

  // use a vector for this instead
  std::unordered_map<Vector3<int32_t>, Block::Type> blocksInChunk;

  ChunkIterator begin() const;

  ChunkIterator end() const;

  // std::vector<std::vector<std::vector<Vector3<int32_t>>>> allBlocksInChunk;
};

/*
  We define 0, 0, 0 of a chunk to be the bottommost, leftmost, backmost
  point of a chunk
 */
class ChunkIterator
    : public std::iterator<std::random_access_iterator_tag, Vector3<int32_t>> {
 public:
  uint32_t width;
  uint32_t length;
  uint32_t height;

  int32_t idx = 0;
  ChunkIterator(int32_t i) : idx(i) {}
  ChunkIterator(uint32_t w, uint32_t l, uint32_t h, int32_t i)
      : idx(i), width(w), height(h), length(l) {}

  bool operator<(const ChunkIterator& other) const {
    return this->idx < other.idx;
  };

  bool operator!=(const ChunkIterator& other) const { return idx != other.idx; }

  ChunkIterator& operator++() {
    idx++;
    return *this;
  }

  Vector3<int32_t> operator*() const {
    // standard for n dimension is idx % dim1, (idx / dim1) % dim2
    // (idx / (dim1 * dim2)) % dim3...
    return Vector3<int32_t>(idx % width, (idx / width) % height,
                            idx / (width * length));
  }
};

inline ChunkIterator Chunk::begin() const {
  return ChunkIterator(width, length, height, 0);
}

inline ChunkIterator Chunk::end() const {
  return ChunkIterator(width * length * height);
}