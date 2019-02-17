#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../math/Tabular.h"

class TileSet;
class Texture;

/*
  TileMaps require a TileSet context
 */
class TileMap {
 public:
  TileMap(int32_t nRowTiles = 2, int32_t nColTiles = 2);

  TileMap(TileSet* tileSet, int32_t nRowTiles = 2, int32_t nColTiles = 2);

  TileMap(std::vector<int32_t>& tiles,
          int32_t nRowTiles = 2,
          int32_t nColTiles = 2);

  TileMap(const std::string& filePath,
          int32_t nRowTiles = 2,
          int32_t nColTiles = 2);

  void setTileSet(TileSet& tileSet);
  std::unique_ptr<Texture> getTexture();

  int32_t getNumTilesPerRow();
  int32_t getNumTilesPerCol();
  int32_t getTotalTiles();

 private:
  Tabular tabular;

  TileSet* tileSet = nullptr;
  std::vector<int32_t> tiles;
};

inline TileMap::TileMap(int32_t nRowTiles, int32_t nColTiles) {
  tabular.width = nRowTiles;
  tabular.height = nColTiles;
}

inline TileMap::TileMap(TileSet* tileSet, int32_t nRowTiles, int32_t nColTiles)
    : TileMap(nRowTiles, nColTiles) {
  this->tileSet = tileSet;
}

inline TileMap::TileMap(std::vector<int32_t>& tiles,
                        int32_t nRowTiles,
                        int32_t nColTiles)
    : TileMap(nRowTiles, nColTiles) {
  this->tiles = tiles;
}

inline void TileMap::setTileSet(TileSet& tileSet) {
  this->tileSet = &tileSet;
}

inline int32_t TileMap::getNumTilesPerRow() {
  return tabular.width;
}

inline int32_t TileMap::getNumTilesPerCol() {
  return tabular.height;
}

inline int32_t TileMap::getTotalTiles() {
  return tabular.getTotalCells();
}