#pragma once

#include <string>

struct SDL_Window;

class Window {
 public:
  Window(std::string& title, int x, int y, int w, int h, uint32_t flags);
  ~Window();

  SDL_Window* getSdlWindow();

 private:
  SDL_Window* sdlWindow;

  std::string title;
};