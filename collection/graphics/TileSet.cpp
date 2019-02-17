
#include "TileSet.h"

#include "Image.h"
#include "Texture.h"

TileSet::TileSet(const std::string& filePath,
                 uint32_t w,
                 uint32_t h,
                 uint32_t hBorder,
                 uint32_t vBorder,
                 uint32_t xOffsetLeft,
                 uint32_t yOffsetTop,
                 uint32_t xOffsetRight,
                 uint32_t xOffsetBottom)
    : TileSet(Image(filePath),
              w,
              h,
              hBorder,
              vBorder,
              xOffsetLeft,
              yOffsetTop,
              xOffsetRight,
              xOffsetBottom) {}

TileSet::TileSet(const Image& image,
                 uint32_t w,
                 uint32_t h,
                 uint32_t hBorder,
                 uint32_t vBorder,
                 uint32_t xOffsetLeft,
                 uint32_t yOffsetTop,
                 uint32_t xOffsetRight,
                 uint32_t yOffsetBottom)
    : tileWidth(w),
      tileHeight(h),
      hBorder(hBorder),
      vBorder(vBorder),
      xOffsetLeft(xOffsetLeft),
      yOffsetTop(yOffsetTop),
      xOffsetRight(xOffsetRight),
      yOffsetBottom(yOffsetBottom) {
  texture = std::make_unique<Texture>(image);
}

// Includes borders
int32_t TileSet::getWidthInPixels() {
  return texture->getWidth();
}
// s = wx + by, x - 1 = y, so y=(s-w)/(w+b)
int32_t TileSet::getWidthInTiles() {
  int32_t totalTilesWidth = getWidthInPixels() - (xOffsetLeft + xOffsetRight);
  return (totalTilesWidth - tileWidth) / (tileWidth + hBorder) + 1;
}

int32_t TileSet::getHeightInPixels() {
  return texture->getHeight();
}

int32_t TileSet::getHeightInTiles() {
  int32_t totalTilesHeight = getHeightInPixels() - yOffsetTop - yOffsetBottom;
  return (totalTilesHeight - tileHeight) / (tileHeight + vBorder) + 1;
}

Texture& TileSet::getTexture() {
  return *texture;
}