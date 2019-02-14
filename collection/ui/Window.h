#pragma once

#include <string>

struct SDL_Window;
struct Renderer;

class Window {
 public:
  Window(std::string& title, int x, int y, int w, int h, uint32_t flags);
  ~Window();

  SDL_Window* getSdlWindow();
  Renderer getRenderer();

 private:
  SDL_Window* sdlWindow;

  std::string title;
};