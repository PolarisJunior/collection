
#include "Mouse.h"
#include <SDL.h>

bool Mouse::right() {
  return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

bool Mouse::left() {
  return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

bool Mouse::middle() {
  return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}

bool Mouse::buttonDown(int32_t button) {
  return downThisFrame[button];
}

bool Mouse::buttonUp(int32_t button) {
  return upThisFrame[button];
}

void Mouse::update() {
  for (auto& b : downThisFrame) {
    b = false;
  }
  for (auto& b : upThisFrame) {
    b = false;
  }
}

Vector2<int32_t> Mouse::pos() {
  Vector2<int32_t> vec;
  SDL_GetMouseState(&vec.x, &vec.y);
  return vec;
}
