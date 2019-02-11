
#include <SDL.h>
#include <iostream>
#include "../gui/Window.h"
#include "../gui/WindowBuilder.h"

int main(int argc, char** argv) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  }
  // if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
  //   SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  // }
  std::cout << "yeet" << std::endl;
  WindowBuilder windowBuilder;
  windowBuilder.setTitle("fizz buzz").setDims(800, 600);
  std::cout << "yeet2" << std::endl;
  Window* window = windowBuilder.getWindow();

  SDL_Delay(5000);
  std::cout << "exiting" << std::endl;
  return EXIT_SUCCESS;
}