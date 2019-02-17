
#include "TileMap.h"

#include "../math//geometry/Rect.h"
#include "Renderer.h"
#include "Texture.h"
#include "TileSet.h"

std::unique_ptr<Texture> TileMap::getTexture() {
  if (!tileSet) {
    return std::unique_ptr<Texture>();
  }
  tiles = {1, 2, 3};
  std::unique_ptr<Texture> texture = std::make_unique<Texture>(128, 128);
  mainRenderer.setTarget(*texture);
  Texture& tileSetTexture = tileSet->getTexture();

  Rect srcRect = tileSet->getTileRect(19);
  mainRenderer.render(tileSetTexture, &srcRect, nullptr);
  mainRenderer.clearTarget();
  return texture;
}