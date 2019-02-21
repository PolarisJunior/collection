#include "Time.h"

#include <SDL.h>

std::chrono::milliseconds Time::getMs() {
  return std::chrono::milliseconds(SDL_GetTicks());
}

uint32_t Time::getTicks() {
  return SDL_GetTicks();
}

std::chrono::seconds Time::getSeconds() {
  return std::chrono::duration_cast<std::chrono::seconds>(getMs());
  // return static_cast<double>(SDL_GetTicks()) / 1000.0;
}
