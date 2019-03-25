
#include "SdlEventPoller.h"
#include <SDL.h>
#include <functional>

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

void SdlEventPoller::addListener(
    uint32_t eventType,
    std::function<void(const SDL_Event&)> callback) {
  listeners[eventType] = callback;
}