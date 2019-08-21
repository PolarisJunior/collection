
#include "Texture2d.h"
#include "TextureAtlas.h"

#include <gl/glew.h>

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

/* We can replace loadformat returning format with justreturning texture2d, and
use that with copy constructor */
Texture2d::Format Texture2d::loadFormat(const std::string& fileName) {
  SDL_Surface* surf = IMG_Load(fileName.c_str());
  int32_t numBytes = surf->pitch * surf->h;
  std::vector<uint8_t> pixelBuffer;

  bool isRgba;
  int32_t width;
  int32_t height;
  uint32_t textureId;

  if (surf) {
    isRgba = SDL_ISPIXELFORMAT_ALPHA(surf->format->format);
    width = surf->w;
    height = surf->h;

    SDL_LockSurface(surf);
    pixelBuffer =
        std::vector(reinterpret_cast<uint8_t*>(surf->pixels),
                    reinterpret_cast<uint8_t*>(surf->pixels) + numBytes);
    SDL_UnlockSurface(surf);
  }
  SDL_FreeSurface(surf);

  int32_t pixelType = GL_RGB;
  if (isRgba) {
    pixelType = GL_RGBA;
  }

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexImage2D(GL_TEXTURE_2D, 0, pixelType, width, height, 0, pixelType,
               GL_UNSIGNED_BYTE, pixelBuffer.data());

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

  glBindTexture(GL_TEXTURE_2D, 0);

  return Texture2d::Format{isRgba, width, height, textureId};
}

Texture2d::Texture2d(const Format& fmt)
    : isRgba(fmt.rgba),
      width(fmt.width),
      height(fmt.height),
      textureId(fmt.texId) {}

Texture2d::Texture2d(const std::string& fileName)
    : Texture2d(loadFormat(fileName)) {}

Texture2d::Texture2d(Texture2d&& other)
    : isRgba(other.isRgba),
      width(other.width),
      height(other.height),
      textureId(other.textureId) {
  other.textureId = 0;
}

Texture2d::Texture2d(const TextureAtlas& atlas)
    : isRgba(atlas.hasAlpha()), width(atlas.width()), height(atlas.height()) {
  glGenTextures(1, &textureId);

  // 0 Texture is active by default
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureId);

  int32_t pixelType = GL_RGB;
  if (isRgba) {
    pixelType = GL_RGBA;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, pixelType, atlas.width(), atlas.height(), 0,
               pixelType, GL_UNSIGNED_BYTE, atlas.dataPointer());

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2d::~Texture2d() {
  glDeleteTextures(1, &textureId);
}

void Texture2d::bind() const {
  glBindTexture(GL_TEXTURE_2D, textureId);
}