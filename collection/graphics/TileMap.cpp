
#include "TileMap.h"

#include "../math//geometry/Rect.h"
#include "Renderer.h"
#include "Texture.h"
#include "TileSet.h"

std::unique_ptr<Texture> TileMap::getTexture() {
  if (!tileSet) {
    return std::unique_ptr<Texture>();
  }

  int32_t tileWidth = tileSet->tileWidth;
  int32_t tileHeight = tileSet->tileHeight;

  std::unique_ptr<Texture> texture = std::make_unique<Texture>(
      tileWidth * getNumTilesPerRow(), tileHeight * getNumTilesPerCol());
  Texture& tileSetTexture = tileSet->getTexture();

  mainRenderer.setTarget(*texture);
  for (int32_t row = 0; row < getNumTilesPerCol(); row++) {
    for (int32_t col = 0; col < getNumTilesPerRow(); col++) {
      int32_t tableIdx = tabular.getIndex(col, row);
      if (tableIdx >= tiles.size()) {
        break;
      }
      Rect srcRect = tileSet->getTileRect(tiles[tableIdx]);
      Rect dstRect = {col * tileWidth, row * tileHeight, tileWidth, tileHeight};
      mainRenderer.render(tileSetTexture, &srcRect, &dstRect);
    }
  }
  mainRenderer.clearTarget();
  return texture;
}