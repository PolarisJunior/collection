#pragma once

#include <cstdint>
#include <unordered_map>
#include "Block.h"

class BlockDatabase {
 public:
  struct TextureData;
  //  returns an id in the texture atlas given a block type and face
  static int32_t getAtlasId(Block::Type blockType, Block::Face face);

  static const std::unordered_map<Block::Type, TextureData> typeToTextureData;

  struct TextureData {
    int16_t topIndex;
    int16_t bottomIndex;

    int16_t rightIndex;
    int16_t leftIndex;

    int16_t forwardIndex;
    int16_t backwardIndex;

    std::unordered_map<Block::Face, int16_t> faceToFaceIndex;

    TextureData(int16_t top, int16_t bot, int16_t side)
        : TextureData(top, bot, side, side, side, side) {}

    TextureData(int16_t top,
                int16_t bot,
                int16_t right,
                int16_t left,
                int16_t forward,
                int16_t backward)
        : topIndex(top),
          bottomIndex(bot),
          rightIndex(right),
          leftIndex(left),
          forwardIndex(forward),
          backwardIndex(backward) {
      using Face = Block::Face;
      faceToFaceIndex[Face::TOP] = topIndex;
      faceToFaceIndex[Face::SIDE] = rightIndex;
      faceToFaceIndex[Face::BOTTOM] = bottomIndex;
    }
  };
};