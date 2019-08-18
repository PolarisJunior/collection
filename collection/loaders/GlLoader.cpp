
#include "GlLoader.h"
#include <gl/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "ui/Window.h"

#ifdef DEBUG
#include <iostream>
#endif

std::string GlLoader::load() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

  // VSync
  if (SDL_GL_SetSwapInterval(1) < 0) {
    return std::string(SDL_GetError());
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  // glFrontFace(GL_CCW);
  glEnable(GL_MULTISAMPLE);

#ifdef DEBUG
  std::cout << "OpenGL successfully loaded" << std::endl;
#endif
  return "";
}
