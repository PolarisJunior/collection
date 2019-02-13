
#pragma once

#include <unordered_map>

union SDL_Event;

class SdlEventPoller {
 public:
  void pollEvents();

  void addListener(uint32_t eventType, void (*callback)(const SDL_Event&));

 private:
  /* TODO */
  // int listeners;
  // add a mapping from keys to listeners?
  std::unordered_map<uint32_t, void (*)(const SDL_Event&)> listeners;
};
