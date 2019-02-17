#pragma once
#include <cstdint>
#include <memory>
#include <string>

class Image;
class Texture;
class TileSet {
 public:
  TileSet(const std::string& filePath, uint32_t w = 32, uint32_t h = 32);
  TileSet(const Image& image, uint32_t w = 32, uint32_t h = 32);

  Texture& getTexture();

 private:
  uint32_t tileWidth;
  uint32_t tileHeight;

  std::unique_ptr<Texture> texture;
};