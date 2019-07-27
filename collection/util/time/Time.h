
#pragma once
#include <chrono>
#include <cstdint>

class Time {
 public:
  // time in seconds since the last update tick, same across
  // all calls in the same loop
  inline static float deltaTime() { return deltaTime_; }

  /* Get Ms since starting */
  static std::chrono::milliseconds getMs();

  static std::chrono::seconds getSeconds();

  static uint32_t getTicks();

  inline static double latestStartLoopTime_ = 0;

  struct Internal {
    // call once at the start of every update loop
    inline static void startLoop(double t) {
      deltaTime_ = static_cast<float>(t - latestStartLoopTime_);
      latestStartLoopTime_ = t;
    }
    inline static void startLoop(uint32_t t) { startLoop((double)t / 1000.0); }
  };

 private:
  inline static float deltaTime_;
};