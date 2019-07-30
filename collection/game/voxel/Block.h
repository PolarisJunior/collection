#pragma once

#include <array>
#include <unordered_map>
#include <utility>

class Block {
 public:
  // Put transparent blocks first, and then we can index
  // if a block type is in the region of transparent blocks
  // we do not cull faces
  enum class Type { AIR, DIRT, GRASS };
  enum class Face { TOP, BOTTOM, SIDE };

  static int32_t getAtlasIndex(Type type, Face face) {
    std::unordered_map<Face, int32_t> faceToIndex = {
        {Face::TOP, 2}, {Face::BOTTOM, 4}, {Face::SIDE, 5}};
    return faceToIndex.at(face);
  }

  static std::pair<int32_t, int32_t> getAtlasPosition() {
    return std::pair<int32_t, int32_t>();
  }

  inline static const std::unordered_map<int32_t, Face> indicesToFaces = {
      {0, Face::TOP},  {1, Face::BOTTOM}, {2, Face::SIDE},
      {3, Face::SIDE}, {4, Face::SIDE},   {5, Face::SIDE}};

  // inline static const std::unordered_map<Type, std::array<int32_t, 3>>
  //     typeToAtlasIndex = {{Type::DIRT, {}}};
};
