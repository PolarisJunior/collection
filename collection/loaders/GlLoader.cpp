
#include "GlLoader.h"
#include <gl/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "ui/Window.h"

std::string GlLoader::load() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GLContext context =
      SDL_GL_CreateContext(Window::getMainWindow().getSdlWindow());
  if (context == nullptr) {
    return std::string(SDL_GetError());
  }

  GLenum glewError = glewInit();

  if (glewError != GLEW_OK) {
    return std::string(
        reinterpret_cast<const char*>((glewGetErrorString(glewError))));
  }

  if (SDL_GL_SetSwapInterval(1) < 0) {
    return std::string(SDL_GetError());
  }

  return "";
}
