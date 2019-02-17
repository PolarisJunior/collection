#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

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

  int32_t getWidthInPixels();
  // ignores borders, maybe rename to getNumTilesInRow
  int32_t getWidthInTiles();

  int32_t getHeightInPixels();
  // ignores borders
  int32_t getHeightInTiles();

  int32_t getNumTiles();

  uint32_t tileWidth;
  uint32_t tileHeight;

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
  return getWidthInTiles() * getHeightInTiles();
}

inline int32_t TileSet::getTileId(int32_t col, int32_t row) {
  int32_t numTiles = getNumTiles();
  return col + row * getWidthInTiles();
}

inline std::pair<int32_t, int32_t> TileSet::getTilePosInTiles(int32_t tileId) {
  std::pair<int32_t, int32_t> pos;

  pos.first = tileId % getWidthInTiles();
  pos.second = tileId / getWidthInTiles();
  return pos;
}

inline std::pair<int32_t, int32_t> TileSet::getTilePosInPixels(int32_t tileId) {
  auto pos = getTilePosInTiles(tileId);
  pos.first *= tileWidth;
  pos.second *= tileHeight;
  return pos;
}
