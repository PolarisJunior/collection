
#pragma once
#include <chrono>
#include <cstdint>

class Time {
 public:
  // time since last update tick, treat as readonly by
  static float deltaTime() { return deltaTime_; }

  /* Get Ms since starting */
  static std::chrono::milliseconds getMs();

  static std::chrono::seconds getSeconds();

  static uint32_t getTicks();

 private:
  static float deltaTime_;
};