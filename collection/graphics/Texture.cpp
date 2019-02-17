
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "../ui/Window.h"
#include "Image.h"
#include "Renderer.h"

Texture::Texture(int32_t w, int32_t h) {
  sdlTexture = SDL_CreateTexture(mainRenderer.getSdlRenderer(),
                                 mainWindow.getPixelFormat(),
                                 SDL_TEXTUREACCESS_TARGET, w, h);
  width = w;
  height = h;
}

Texture::Texture(char* buf, int32_t bufSize, const std::string& type) {
  SDL_RWops* rw = SDL_RWFromConstMem(buf, bufSize);
  // putting 1 as arg makes it automatically free
  SDL_Surface* surface = IMG_LoadTyped_RW(rw, 1, type.c_str());
  sdlTexture = mainRenderer.createTextureFromSurface(surface);

  if (surface) {
    width = surface->w;
    height = surface->h;
  }

  SDL_FreeSurface(surface);
  SDL_FreeRW(rw);
}

Texture::Texture(const Image& image)
    : Texture(image.buf.get(), image.getImageSize(), image.getType()) {}

Texture::Texture(const std::string& filePath) : Texture(Image(filePath)) {}

Texture::~Texture() {
  SDL_DestroyTexture(sdlTexture);
}