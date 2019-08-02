
#include "WindowBuilder.h"
#include <SDL.h>
#include "Window.h"

WindowBuilder::WindowBuilder() {
  xPos = SDL_WINDOWPOS_UNDEFINED;
  yPos = SDL_WINDOWPOS_UNDEFINED;
  flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
}

WindowBuilder& WindowBuilder::setTitle(const std::string& title) {
  this->title = title;
  return *this;
}

WindowBuilder& WindowBuilder::setWidth(int w) {
  this->width = w;
  return *this;
}

WindowBuilder& WindowBuilder::setHeight(int h) {
  this->height = h;
  return *this;
}

WindowBuilder& WindowBuilder::setDims(int w, int h) {
  this->width = w;
  this->height = h;

  return *this;
}

WindowBuilder& WindowBuilder::setPos(int x, int y) {
  this->xPos = x;
  this->yPos = y;
  return *this;
}

WindowBuilder& WindowBuilder::setFlags(uint32_t flags) {
  this->flags = flags;
  return *this;
}

WindowBuilder& WindowBuilder::setVisible() {
  this->flags |= SDL_WINDOW_SHOWN;
  return *this;
}

WindowBuilder& WindowBuilder::setResizable() {
  this->flags |= SDL_WINDOW_RESIZABLE;
  return *this;
}

WindowBuilder& WindowBuilder::fullScreen() {
  this->flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  return *this;
}

Window WindowBuilder::getWindow() {
  return Window(this->title, xPos, yPos, width, height, flags);
}
