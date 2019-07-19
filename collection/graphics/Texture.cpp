
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "graphics/Image.h"
#include "graphics/Renderer.h"
#include "ui/Window.h"

Texture::Texture(int32_t w, int32_t h) {
  sdlTexture = SDL_CreateTexture(Window::getMainRenderer().getSdlRenderer(),
                                 Window::getMainWindow().getPixelFormat(),
                                 SDL_TEXTUREACCESS_TARGET, w, h);
  width = w;
  height = h;
}

Texture::Texture(char* buf, int32_t bufSize, const std::string& type) {
  SDL_RWops* rw = SDL_RWFromConstMem(buf, bufSize);
  // putting 1 as arg makes it automatically free
  SDL_Surface* surface = IMG_LoadTyped_RW(rw, 1, type.c_str());
  sdlTexture = Window::getMainRenderer().createTextureFromSurface(surface);

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

void Texture::render(int32_t x, int32_t y, Renderer& renderer) {
  renderer.render(*this, x, y);
}

void Texture::render(int32_t x, int32_t y) {
  this->render(x, y, Window::getMainRenderer());
}

Texture::~Texture() {
  SDL_DestroyTexture(sdlTexture);
}