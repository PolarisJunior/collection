
#include "Renderer.h"
#include <SDL.h>
#include "../math/geometry/Rect.h"
#include "Color.h"

// Renderer mainRenderer;

void Renderer::present() {
  SDL_RenderPresent(sdlRenderer);
}

void Renderer::clear() {
  SDL_RenderClear(sdlRenderer);
}

void Renderer::setColor(const Color& color) {
  SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
}

void Renderer::drawRect(const Rect& rect) {
  SDL_RenderDrawRect(sdlRenderer, reinterpret_cast<const SDL_Rect*>(&rect));
}
