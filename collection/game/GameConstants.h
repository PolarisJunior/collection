#pragma once

#include <cstdint>

class GameConstants {
 public:
  constexpr static float frameRate() { return 60; }
  constexpr static float frameTime() { return 1.0 / frameRate(); }

  inline static const uint32_t MAX_LOOPS = 10;

 private:
  inline static const uint32_t UPDATE_FREQUENCY = 60;
  inline static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
};
