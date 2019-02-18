
#include "Window.h"
#include <SDL.h>
#include "../graphics/Renderer.h"

Window::Window(std::string& title, int x, int y, int w, int h, uint32_t flags)
    : title(title) {
  sdlWindow = SDL_CreateWindow(this->title.c_str(), x, y, w, h, flags);
  if (!sdlWindow) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

Window::~Window() {
  SDL_DestroyWindow(sdlWindow);
}

SDL_Window* Window::getSdlWindow() {
  return sdlWindow;
}

Renderer Window::getRenderer() {
  SDL_Renderer* r =
      SDL_CreateRenderer(sdlWindow, -1,
                         SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED |
                             SDL_RENDERER_PRESENTVSYNC);
  if (!r) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Renderer o(r);
  // return o;
  // NOTE notice this doesn't call copy constructor
  return Renderer(r);
}

int32_t Window::getWidth() {
  int32_t w;
  SDL_GetWindowSize(sdlWindow, &w, nullptr);
  return w;
}

int32_t Window::getHeight() {
  int32_t h;
  SDL_GetWindowSize(sdlWindow, nullptr, &h);
  return h;
}

uint32_t Window::getPixelFormat() {
  return SDL_GetWindowPixelFormat(getSdlWindow());
}

Window& Window::operator=(Window&& other) {
  swap(*this, other);
  return *this;
}

void swap(Window& first, Window& second) {
  using std::swap;
  swap(first.sdlWindow, second.sdlWindow);
  swap(first.title, second.title);
}