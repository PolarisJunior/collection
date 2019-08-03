#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "util/Size2d.h"

// A texture in OpenGL
class Texture2d : public Size2d<int32_t> {
 public:
  Texture2d(const std::string& fileName);

  bool isRgba() const { return isRgba_; }

  // uint8_t* data() const

 private:
  bool isRgba_ = false;
  // std::vector<uint8_t> pixelBuffer;

  uint32_t textureId;
};
