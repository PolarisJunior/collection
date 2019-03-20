
#include "Renderer.h"
#include <SDL.h>
#include <iostream>
#include "../math/geometry/Rect.h"
#include "../ui/Window.h"
#include "Color.h"
#include "Texture.h"

Renderer::Renderer(Window& window) : Renderer(window.getRenderer()) {}

Renderer::~Renderer() {
  // std::cout << "deconstructing addr:" << sdlRenderer << std::endl;
  SDL_DestroyRenderer(sdlRenderer);
}

Renderer::Renderer(Renderer&& other) {
  // std::cout << "construct" << std::endl;
  swap(*this, other);
}

void Renderer::present() {
  SDL_RenderPresent(sdlRenderer);
}

void Renderer::clear() {
  SDL_RenderClear(sdlRenderer);
}

void Renderer::render(Texture& texture,
                      const Rect<int32_t>& src,
                      const Rect<int32_t>& dst) {
  SDL_RenderCopy(sdlRenderer, texture.getSdlTexture(),
                 reinterpret_cast<const SDL_Rect*>(&src),
                 reinterpret_cast<const SDL_Rect*>(&dst));
}

void Renderer::render(Texture& texture,
                      Rect<int32_t>* src,
                      Rect<int32_t>* dst) {
  SDL_RenderCopy(sdlRenderer, texture.getSdlTexture(),
                 reinterpret_cast<SDL_Rect*>(src),
                 reinterpret_cast<SDL_Rect*>(dst));
}

void Renderer::render(Texture& texture, int32_t x, int32_t y) {
  Rect<int32_t> dstRect = {x, y, texture.getWidth(), texture.getHeight()};
  render(texture, nullptr, &dstRect);
}

void Renderer::render(Texture& texture) {
  SDL_RenderCopy(sdlRenderer, texture.getSdlTexture(), nullptr, nullptr);
}

void Renderer::setColor(const Color& color) {
  SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
}

void Renderer::setTarget(Texture& targ) {
  SDL_SetRenderTarget(getSdlRenderer(), targ.getSdlTexture());
}

void Renderer::clearTarget() {
  SDL_SetRenderTarget(getSdlRenderer(), nullptr);
}

void Renderer::drawRect(const Rect<int32_t>& rect) {
  SDL_RenderDrawRect(sdlRenderer, reinterpret_cast<const SDL_Rect*>(&rect));
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface) {
  SDL_Texture* tex = SDL_CreateTextureFromSurface(getSdlRenderer(), surface);
  return tex;
}

Renderer& Renderer::operator=(Renderer other) {
  swap(*this, other);
  return *this;
}

// Renderer& Renderer::operator=(Renderer&& other) {
//   std::cout << "option 2" << std::endl;
//   swap(*this, other);
//   return *this;
// }

void swap(Renderer& first, Renderer& second) {
  using std::swap;
  swap(first.sdlRenderer, second.sdlRenderer);
}