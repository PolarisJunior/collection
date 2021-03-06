
#include "BlockDatabase.h"

using Db = BlockDatabase;
using Type = Block::Type;

const std::unordered_map<Block::Type, Db::TextureData> Db::typeToTextureData = {
    // {Type::DIRT, Db::TextureData(3, 3, 3)},
    // {Type::GRASS, Db::TextureData(6, 3, 0)}
    {Type::DIRT, Db::TextureData(1, 1, 1)},
    {Type::GRASS, Db::TextureData(2, 1, 0)}};

int32_t Db::getAtlasId(Block::Type blockType, Block::Face blockFace) {
  auto it = Db::typeToTextureData.find(blockType);

  if (it != typeToTextureData.end()) {
    const BlockDatabase::TextureData texData = it->second;
    return texData.faceToFaceIndex.at(blockFace);
  }

  return 0;
}