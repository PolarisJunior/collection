
#include "TextureAtlas.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <iterator>
#include "math/Vector2.h"

TextureAtlas::TextureAtlas(const std::string& imgPath, int32_t cw, int32_t ch)
    : cellWidth(cw), cellHeight(ch), pixelBuffer(std::vector<uint8_t>()) {
  SDL_Surface* surf = IMG_Load(imgPath.c_str());
  int32_t numBytes = surf->pitch * surf->h;

  if (surf != nullptr) {
    hasAlpha_ = SDL_ISPIXELFORMAT_ALPHA(surf->format->format);
    width_ = surf->w;
    height_ = surf->h;

    SDL_LockSurface(surf);
    pixelBuffer =
        std::vector(reinterpret_cast<uint8_t*>(surf->pixels),
                    reinterpret_cast<uint8_t*>(surf->pixels) + numBytes);
    SDL_UnlockSurface(surf);
  }

  SDL_FreeSurface(surf);
}

std::array<Vec2, 6> TextureAtlas::getFaceTexCoords(int32_t row,
                                                   int32_t col) const {
  std::array<Vec2, 6> texCoords;
  return texCoords;
}

const uint8_t* TextureAtlas::dataPointer() const {
  return pixelBuffer.data();
}