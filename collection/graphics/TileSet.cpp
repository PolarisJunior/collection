
#include "TileSet.h"

#include "Image.h"
#include "Texture.h"

TileSet::TileSet(const std::string& filePath,
                 uint32_t w,
                 uint32_t h,
                 uint32_t hBorder,
                 uint32_t vBorder,
                 uint32_t xOffset,
                 uint32_t yOffset)
    : TileSet(Image(filePath), w, h, hBorder, vBorder, xOffset, yOffset) {}

TileSet::TileSet(const Image& image,
                 uint32_t w,
                 uint32_t h,
                 uint32_t hBorder,
                 uint32_t vBorder,
                 uint32_t xOffset,
                 uint32_t yOffset)
    : tileWidth(w),
      tileHeight(h),
      hBorder(hBorder),
      vBorder(vBorder),
      xOffset(xOffset),
      yOffset(yOffset) {
  texture = std::make_unique<Texture>(image);
}

Texture& TileSet::getTexture() {
  return *texture;
}