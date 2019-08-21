#pragma once

#include <cstdint>
#include <string>
#include <vector>

class TextureAtlas;

// A texture in OpenGL
class Texture2D {
  struct Format {
    bool rgba;
    int32_t width;
    int32_t height;
    uint32_t texId;
  };

  Texture2D(const Format& fmt);

 public:
  Texture2D(const std::string& fileName);
  Texture2D(Texture2D&& other);
  Texture2D(const TextureAtlas& atlas);
  ~Texture2D();

  void Bind() const;

  uint32_t textureId;
  const int32_t width;
  const int32_t height;
  const bool isRgba;

 private:
  static Format loadFormat(const std::string& fileName);
};
