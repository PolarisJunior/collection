
#include "SdlEventPoller.h"
#include <SDL.h>
#include <functional>

#include "game/Camera.h"
#include "game/GameInstance.h"

#include "math/Ray.h"
#include "ui/Mouse.h"

typedef void (*Callback)(const SDL_Event&);

static SdlEventPoller eventPoller;

SdlEventPoller::SdlEventPoller() {
  static bool wasInitialized = false;
  if (wasInitialized) {
    return;
  }

  addListener(SDL_KEYUP, [](const SDL_Event& event) {
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        break;
      case SDLK_RIGHT:
        break;
      case SDLK_DOWN:
        break;
      case SDLK_LEFT:
        break;
    }
  });

  addListener(SDL_KEYDOWN, [](const SDL_Event& event) {
    if (event.key.repeat) {
      return;
    }
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        break;
      case SDLK_RIGHT:
        break;
      case SDLK_DOWN:
        break;
      case SDLK_LEFT:
        break;
    }
  });

  addListener(SDL_QUIT,
              [](const SDL_Event& event) { GameInstance::isRunning = false; });

  SdlEventPoller::addListener(SDL_MOUSEBUTTONDOWN, [](const SDL_Event& event) {
    Ray ray = Camera::getMainCamera().screenPointToRay(
        Vec2(event.button.x, event.button.y));
    Mouse::downThisFrame[0] = true;
  });

  wasInitialized = true;
}

void SdlEventPoller::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (listeners.count(event.type)) {
      listeners[event.type](event);
    }
  }
}

void SdlEventPoller::addListener(
    uint32_t eventType,
    std::function<void(const SDL_Event&)> callback) {
  listeners[eventType] = callback;
}
