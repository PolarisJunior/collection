
#include "TextureAtlas.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>

TextureAtlas::TextureAtlas(const std::string& imgPath, int32_t cw, int32_t ch) {
  SDL_Surface* surf = IMG_Load(imgPath.c_str());
  int32_t numBytes = surf->pitch * surf->h;

  if (surf != nullptr) {
    hasAlpha_ = SDL_ISPIXELFORMAT_ALPHA(surf->format->format);
    width_ = surf->w;
    height_ = surf->h;

    SDL_LockSurface(surf);

    std::copy(reinterpret_cast<uint8_t*>(surf->pixels),
              reinterpret_cast<uint8_t*>(surf->pixels) + numBytes,
              std::back_inserter(pixelBuffer));

    SDL_UnlockSurface(surf);
  }

  SDL_FreeSurface(surf);
}

uint8_t* TextureAtlas::dataPointer() {
  return pixelBuffer.data();
}