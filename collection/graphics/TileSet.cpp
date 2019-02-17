
#include "TileSet.h"

#include "Image.h"
#include "Texture.h"

TileSet::TileSet(const std::string& filePath, uint32_t w, uint32_t h)
    : TileSet(Image(filePath), w, h) {}

TileSet::TileSet(const Image& image, uint32_t w, uint32_t h)
    : tileWidth(w), tileHeight(h) {
  texture = std::make_unique<Texture>(image);
}

Texture& TileSet::getTexture() {
  return *texture;
}