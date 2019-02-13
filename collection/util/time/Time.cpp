#include "Time.h"

#include <SDL.h>

uint32_t Time::getMs() {
  return SDL_GetTicks();
}

uint32_t Time::getSeconds() {
  return SDL_GetTicks() / 1000;
}