#include "Time.h"

#include <SDL.h>

uint32_t Time::getMs() {
  return SDL_GetTicks();
}

double Time::getSeconds() {
  return static_cast<double>(SDL_GetTicks()) / 1000.0;
}