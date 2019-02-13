
#include "SdlEventPoller.h"
#include <SDL.h>

typedef void (*Callback)(const SDL_Event&);

void SdlEventPoller::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (listeners.count(event.type)) {
      listeners[event.type](event);
    }
    // SDL_EventType
  }
}

void SdlEventPoller::addListener(uint32_t eventType, Callback callback) {
  listeners[eventType] = callback;
}