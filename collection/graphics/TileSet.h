#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include "../math/geometry/Rect.h"

class Image;
class Texture;

class TileSet {
 public:
  TileSet(const std::string& filePath,
          uint32_t w = 32,
          uint32_t h = 32,
          uint32_t hBorder = 0,
          uint32_t vBorder = 0,
          uint32_t xOffsetLeft = 0,
          uint32_t yOffsetTop = 0,
          uint32_t xOffsetRight = 0,
          uint32_t yOffsetBottom = 0);

  TileSet(const Image& image,
          uint32_t w = 32,
          uint32_t h = 32,
          uint32_t hBorder = 0,
          uint32_t vBorder = 0,

          uint32_t xOffsetLeft = 0,
          uint32_t yOffsetRight = 0,
          uint32_t xOffsetRight = 0,
          uint32_t yOffsetBottom = 0);

  Texture& getTexture();

  int32_t getTileId(int32_t col, int32_t row);
  std::pair<int32_t, int32_t> getTilePosInPixels(int32_t tileId);
  std::pair<int32_t, int32_t> getTilePosInTiles(int32_t tileId);
  Rect getTileRect(int32_t tileId);

  int32_t getWidthInPixels();
  int32_t getTilesPerRow();

  int32_t getHeightInPixels();
  int32_t getTilesPerCol();

  int32_t getNumTiles();

  uint32_t tileWidth;
  uint32_t tileHeight;

  /* border around each tile */
  uint32_t hBorder;
  uint32_t vBorder;

  uint32_t xOffsetLeft;
  uint32_t xOffsetRight;

  uint32_t yOffsetTop;
  uint32_t yOffsetBottom;

 private:
  std::unique_ptr<Texture> texture;
};

inline int32_t TileSet::getNumTiles() {
  return getTilesPerRow() * getTilesPerCol();
}

inline int32_t TileSet::getTileId(int32_t col, int32_t row) {
  int32_t numTiles = getNumTiles();
  return col + row * getTilesPerRow();
}

inline std::pair<int32_t, int32_t> TileSet::getTilePosInTiles(int32_t tileId) {
  std::pair<int32_t, int32_t> pos;

  pos.first = tileId % getTilesPerRow();
  pos.second = tileId / getTilesPerRow();
  return pos;
}

inline std::pair<int32_t, int32_t> TileSet::getTilePosInPixels(int32_t tileId) {
  auto pos = getTilePosInTiles(tileId);
  pos.first = tileWidth * pos.first + xOffsetLeft + pos.first * hBorder;
  pos.second = tileHeight * pos.second + yOffsetTop + pos.second * vBorder;
  return pos;
}

inline Rect TileSet::getTileRect(int32_t tileId) {
  auto pos = getTilePosInPixels(tileId);
  return {(int32_t)pos.first, (int32_t)pos.second, (int32_t)tileWidth,
          (int32_t)tileHeight};
}
