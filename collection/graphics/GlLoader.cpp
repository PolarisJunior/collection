
#include "GlLoader.h"
#include <gl/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "ui/Window.h"

void GlLoader::initialize() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GLContext context =
      SDL_GL_CreateContext(Window::getMainWindow().getSdlWindow());
  if (context == nullptr) {
    std::cout << "failed to create gl context: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cout << "Error initializing glew: " << glewGetErrorString(glewError)
              << std::endl;
    exit(-1);
  }

  if (SDL_GL_SetSwapInterval(1) < 0) {
    std::cout << "Unable to set VSync: " << SDL_GetError() << std::endl;
  }
}
