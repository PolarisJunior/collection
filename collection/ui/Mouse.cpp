
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

Vector2<int32_t> Mouse::pos() {
  Vector2<int32_t> vec;
  SDL_GetMouseState(&vec.x, &vec.y);
  return vec;
}
