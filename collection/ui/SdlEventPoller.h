
#pragma once

#include <functional>
#include <unordered_map>

union SDL_Event;

class SdlEventPoller {
 public:
  SdlEventPoller();

  void pollEvents();

  // void addListener(uint32_t eventType, void (*callback)(const SDL_Event&));
  void addListener(uint32_t eventType,
                   std::function<void(const SDL_Event&)> callback);

 private:
  /* TODO */
  // int listeners;
  // add a mapping from keys to listeners?
  // std::unordered_map<uint32_t, void (*)(const SDL_Event&)> listeners;
  std::unordered_map<uint32_t, std::function<void(const SDL_Event&)>> listeners;
};
