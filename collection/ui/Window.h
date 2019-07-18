#pragma once

#include <memory>
#include <string>

struct SDL_Window;
struct Renderer;
// class Window;
class WindowBuilder;

/*
NOTE: WE CANNOT USE THE PIMPL IDIOM WITH UNIQUE PTRS AND
SDL CLASSES BECAUSE THEIR STRUCTS ARE ALWAYS INCOMPLETE TYPES
 */
class Window {
 public:
  //  if we use PIMPL The constructor needs access to the complete type so we
  //  need to define it
  // in the cpp file
  // Window();
  Window() = default;
  Window(std::string& title, int x, int y, int w, int h, uint32_t flags);
  ~Window();

  SDL_Window* getSdlWindow();
  Renderer getRenderer(bool vSync = false);

  int32_t getWidth();
  int32_t getHeight();

  uint32_t getPixelFormat();

  Window& operator=(Window&& other);
  friend void swap(Window& first, Window& second);

  static void initMainWindow(WindowBuilder& builder);
  // static void setMainWindow(Window& window);
  static Window& getMainWindow();
  // interestingly this works
  static Window mainWindow;

 private:
  SDL_Window* sdlWindow;
  std::string title;
};
