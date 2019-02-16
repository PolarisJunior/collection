
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
  SDL_Renderer* r = SDL_CreateRenderer(
      sdlWindow, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
  if (!r) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
    exit(EXIT_FAILURE);
  }
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