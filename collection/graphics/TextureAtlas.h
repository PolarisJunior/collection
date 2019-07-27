#pragma once

#include <array>
#include <string>
#include <vector>
#include "graphics/Image.h"
#include "math/Mathf.h"
#include "math/Vector2.h"

class TextureAtlas {
 public:
  TextureAtlas(const std::string& imgPath, int32_t cw = 16, int32_t ch = 16);

  int32_t width() const { return width_; }
  int32_t height() const { return height_; }

  std::array<Vec2, 6> getFaceTexCoords(int32_t row, int32_t col) const;

  void setSize(int32_t w, int32_t h) {
    width_ = w;
    height_ = h;
  }

  int32_t numRows() const { return height() / cellHeight; }
  int32_t numCols() const { return width() / cellWidth; }
  int32_t texturesPerRow() const { return numCols(); }
  int32_t texturesPerCol() const { return numRows(); }

  // returns the texture index at row, col
  int32_t textureIndex(int32_t row, int32_t col) const {
    return col + row * texturesPerRow();
  }

  bool hasAlpha() { return hasAlpha_; }

  uint8_t* dataPointer();

  // should be the same, and in powers of two
  int32_t cellWidth = 16;
  int32_t cellHeight = 16;

 private:
  // should be the same, and in powers of two
  int32_t width_ = 512;
  int32_t height_ = 512;

  bool hasAlpha_ = false;

  std::vector<uint8_t> pixelBuffer;
};
