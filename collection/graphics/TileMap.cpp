
#include "TileMap.h"

#include <algorithm>
#include <vector>
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "graphics/TileSet.h"
#include "io/FileInputStream.h"
#include "math/geometry/Rect.h"
#include "ui/Window.h"
#include "util/stringUtils.h"

std::unique_ptr<Texture> TileMap::getTexture() {
  if (!tileSet) {
    return std::unique_ptr<Texture>();
  }

  int32_t tileWidth = tileSet->tileWidth;
  int32_t tileHeight = tileSet->tileHeight;

  std::unique_ptr<Texture> texture = std::make_unique<Texture>(
      tileWidth * getNumTilesPerRow(), tileHeight * getNumTilesPerCol());
  Texture& tileSetTexture = tileSet->getTexture();

  Window::getMainRenderer().setTarget(*texture);
  for (int32_t row = 0; row < getNumTilesPerCol(); row++) {
    for (int32_t col = 0; col < getNumTilesPerRow(); col++) {
      int32_t tableIdx = tabular.getIndex(col, row);
      if (tableIdx >= tiles.size()) {
        break;
      }
      Rect<int32_t> srcRect = tileSet->getTileRect(tiles[tableIdx]);
      Rect<int32_t> dstRect = {col * tileWidth, row * tileHeight, tileWidth,
                               tileHeight};

      Window::getMainRenderer().render(tileSetTexture, &srcRect, &dstRect);
    }
  }
  Window::getMainRenderer().clearTarget();
  return texture;
}

std::optional<TileMap> TileMap::loadMapFromCsv(const std::string& filePath) {
  std::optional<FileInputStream> inputStream =
      FileInputStream::getStream(filePath);

  std::vector<int32_t> tiles;
  if (inputStream) {
    std::string line = inputStream->readLine();
    std::vector<std::string> tokens = stringSplit(line, ',');
    int32_t width = static_cast<int32_t>(tokens.size());

    if (width < 1) {
      return std::nullopt;
    }

    for (auto& s : tokens) {
      tiles.push_back(std::stoi(s));
    }

    while (inputStream->hasNext()) {
      line = inputStream->readLine();
      tokens = stringSplit(line, ',');
      for (auto& s : tokens) {
        tiles.push_back(std::stoi(s));
      }
    }

    int32_t height = tiles.size() / width;
    return std::optional<TileMap>(TileMap(tiles, width, height));
  }
  return std::nullopt;
}