#pragma once

#include <memory>
#include <string>
#include <vector>

class TileSet;
class Texture;

/*
  TileMaps require a TileSet context
 */
class TileMap {
 public:
  TileMap() = default;
  TileMap(const std::string& filePath);

  void setTileSet(TileSet& tileSet);
  std::unique_ptr<Texture> getTexture();

 private:
  TileSet* tileSet = nullptr;
  std::vector<int32_t> tiles;
};

inline void TileMap::setTileSet(TileSet& tileSet) {
  this->tileSet = &tileSet;
}