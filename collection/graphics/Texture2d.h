#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "util/Size2d.h"

// A texture in OpenGL
class Texture2d {
  struct Format {
    bool rgba;
    int32_t width;
    int32_t height;
    uint32_t texId;
  };

  Texture2d(const Format& fmt);

 public:
  Texture2d(const std::string& fileName);

  const uint32_t textureId;
  const int32_t width;
  const int32_t height;

  const bool isRgba;

 private:
  static Format loadFormat(const std::string& fileName);
};
