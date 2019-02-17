#pragma once

#include <string>

struct SDL_Window;
struct Renderer;

class Window {
 public:
  Window() = default;
  Window(std::string& title, int x, int y, int w, int h, uint32_t flags);
  ~Window();

  SDL_Window* getSdlWindow();
  Renderer getRenderer();

  int32_t getWidth();
  int32_t getHeight();

  Window& operator=(Window&& other);
  friend void swap(Window& first, Window& second);

 private:
  SDL_Window* sdlWindow;

  std::string title;
};

extern Window mainWindow;