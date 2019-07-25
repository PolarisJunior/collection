#pragma once

#include <string>
#include <vector>
#include "graphics/Image.h"
#include "math/Mathf.h"

class TextureAtlas {
 public:
  TextureAtlas(const std::string& imgPath, int32_t cw = 16, int32_t ch = 16);

  int32_t width() { return width_; }
  int32_t height() { return height_; }

  void setSize(int32_t w, int32_t h) {
    width_ = w;
    height_ = h;
  }

  void setCellSize(int32_t w, int32_t h) {
    cellWidth = w;
    cellHeight = h;
  }

  bool hasAlpha() { return hasAlpha_; }

  uint8_t* dataPointer();

 private:
  // should be the same, and in powers of two
  int32_t width_ = 512;
  int32_t height_ = 512;

  // should be the same, and in powers of two
  int32_t cellWidth = 16;
  int32_t cellHeight = 16;

  bool hasAlpha_ = false;

  std::vector<uint8_t> pixelBuffer;
};
