
#include "Texture2d.h"
#include <SDL.h>
#include <SDL_image.h>
#include <gl/glew.h>

Texture2d::Texture2d(const std::string& fileName) {
  SDL_Surface* surf = IMG_Load(fileName.c_str());
  int32_t numBytes = surf->pitch * surf->h;
  std::vector<uint8_t> pixelBuffer;

  if (surf) {
    isRgba_ = SDL_ISPIXELFORMAT_ALPHA(surf->format->format);
    width_ = surf->w;
    height_ = surf->h;

    SDL_LockSurface(surf);
    pixelBuffer =
        std::vector(reinterpret_cast<uint8_t*>(surf->pixels),
                    reinterpret_cast<uint8_t*>(surf->pixels) + numBytes);
    SDL_UnlockSurface(surf);
  }
  SDL_FreeSurface(surf);

  int32_t pixelType = GL_RGB;
  if (isRgba()) {
    pixelType = GL_RGBA;
  }

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexImage2D(GL_TEXTURE_2D, 0, pixelType, width(), height(), 0, pixelType,
               GL_UNSIGNED_BYTE, pixelBuffer.data());

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

  glBindTexture(GL_TEXTURE_2D, 0);
}
