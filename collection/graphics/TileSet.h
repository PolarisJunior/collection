#pragma once
#include <cstdint>
#include <memory>
#include <string>

class Image;
class Texture;

class TileSet {
 public:
  TileSet(const std::string& filePath,
          uint32_t w = 32,
          uint32_t h = 32,
          uint32_t hBorder = 0,
          uint32_t vBorder = 0,
          uint32_t xOffset = 0,
          uint32_t yOffset = 0);

  TileSet(const Image& image,
          uint32_t w = 32,
          uint32_t h = 32,
          uint32_t hBorder = 0,
          uint32_t vBorder = 0,
          uint32_t xOffset = 0,
          uint32_t yOffset = 0);

  Texture& getTexture();

  uint32_t tileWidth;
  uint32_t tileHeight;

  uint32_t hBorder;
  uint32_t vBorder;

  uint32_t xOffset;
  uint32_t yOffset;

 private:
  std::unique_ptr<Texture> texture;
};