
#include "Window.h"
#include <SDL.h>
#include "graphics/Renderer.h"
#include "ui/WindowBuilder.h"

Window Window::mainWindow;

Window::Window(std::string& title,
               int x,
               int y,
               int w,
               int h,
               uint32_t flags,
               bool initRenderer,
               bool vSync)
    : title(title),
      sdlWindow(SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) {
  if (!sdlWindow) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (initRenderer) {
    uint32_t flags = SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED;
    if (vSync) {
      flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    SDL_Renderer* r = SDL_CreateRenderer(sdlWindow, -1, flags);
    if (!r) {
      SDL_LogError(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
      exit(EXIT_FAILURE);
    }

    windowRenderer = std::make_unique<Renderer>(r);
  }
}

Window::~Window() {
  delete sdlWindow;
};

SDL_Window* Window::getSdlWindow() {
  return sdlWindow;
}

Renderer& Window::getRenderer() {
  return *windowRenderer;
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

void Window::initMainWindow(WindowBuilder& builder) {
  // This works because builder immediately returns after calling the
  // constructor
  Window::mainWindow = builder.getWindow();
}

// It is unintuitive if we cannabalize the window passed in
// void Window::setMainWindow(Window& window) {
//   Window::mainWindow = std::move(window);
// }

Window& Window::getMainWindow() {
  return Window::mainWindow;
}

Renderer& Window::getMainRenderer() {
  return getMainWindow().getRenderer();
}
