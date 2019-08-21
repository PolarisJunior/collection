
#include "SdlEventPoller.h"
#include <SDL.h>
#include <functional>

#include "game/Camera.h"
#include "game/GameInstance.h"

#include "math/Ray.h"
#include "ui/Keyboard.h"
#include "ui/Mouse.h"

typedef void (*Callback)(const SDL_Event&);

static SdlEventPoller eventPoller;

const std::unordered_map<uint8_t, Mouse::Button> button_dict = {
    {SDL_BUTTON_LEFT, Mouse::Button::LEFT},
    {SDL_BUTTON_RIGHT, Mouse::Button::RIGHT},
    {SDL_BUTTON_MIDDLE, Mouse::Button::MIDDLE}};

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
    Keyboard::NotifyKeyPressed(event.key.keysym.scancode);
  });

  addListener(SDL_QUIT,
              [](const SDL_Event& event) { GameInstance::isRunning = false; });

  SdlEventPoller::addListener(SDL_MOUSEBUTTONDOWN, [](const SDL_Event& event) {
    Ray ray = Camera::getMainCamera().screenPointToRay(
        Vec2(event.button.x, event.button.y));
    const auto& bt = button_dict.find(event.button.button);
    if (bt != button_dict.end()) {
      Mouse::downThisFrame[Mouse::ButtonToIndex(bt->second)] = true;
    }
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
