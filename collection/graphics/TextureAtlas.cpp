
#include "TextureAtlas.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "math/Vector2.h"

TextureAtlas::TextureAtlas(const std::string& imgPath, int32_t cw, int32_t ch)
    : cellWidth(cw), cellHeight(ch), pixelBuffer(std::vector<uint8_t>()) {
  std::cout << "IMG_LOAD" << std::endl;
  SDL_Surface* surf = IMG_Load(imgPath.c_str());
  int32_t numBytes = surf->pitch * surf->h;

  if (surf != nullptr) {
    hasAlpha_ = SDL_ISPIXELFORMAT_ALPHA(surf->format->format);
    width_ = surf->w;
    height_ = surf->h;

    SDL_LockSurface(surf);

    std::cout << "INSERTING TO VECTOR" << std::endl;
    // slow
    // pixelBuffer.reserve(numBytes);
    // auto first = reinterpret_cast<uint8_t*>(surf->pixels);
    // auto const last = std::next(first, numBytes);
    // while (first != last) {
    //   pixelBuffer.push_back(*first);
    //   ++first;
    // }

    // fast
    // pixelBuffer.resize(numBytes);
    // std::copy(reinterpret_cast<uint8_t*>(surf->pixels),
    //           reinterpret_cast<uint8_t*>(surf->pixels) + numBytes,
    //           pixelBuffer.data());

    // fast
    // pixelBuffer.reserve(numBytes);
    // std::copy(reinterpret_cast<uint8_t*>(surf->pixels),
    //           reinterpret_cast<uint8_t*>(surf->pixels) + numBytes,
    //           pixelBuffer._Unchecked_begin());

    // fast
    // pixelBuffer.resize(numBytes);
    // std::copy(reinterpret_cast<uint8_t*>(surf->pixels),
    //           reinterpret_cast<uint8_t*>(surf->pixels) + numBytes,
    //           pixelBuffer.begin());

    // fast
    // pixelBuffer.resize(numBytes);
    // std::move(reinterpret_cast<uint8_t*>(surf->pixels),
    //           reinterpret_cast<uint8_t*>(surf->pixels) + numBytes,
    //           pixelBuffer.begin());

    pixelBuffer.insert(pixelBuffer.begin(),
                       reinterpret_cast<uint8_t*>(surf->pixels),
                       reinterpret_cast<uint8_t*>(surf->pixels) + numBytes);
    std::cout << "INSERTION DONE" << std::endl;
    SDL_UnlockSurface(surf);
  }

  SDL_FreeSurface(surf);
}

std::array<Vec2, 6> TextureAtlas::getFaceTexCoords(int32_t row,
                                                   int32_t col) const {
  std::array<Vec2, 6> texCoords;
  return texCoords;
}

uint8_t* TextureAtlas::dataPointer() {
  return pixelBuffer.data();
}