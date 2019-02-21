#pragma once
#include <chrono>
#include <cstdint>
#include "Time.h"

class Timer {
 public:
  Timer();
  ~Timer() = default;

  void startTimer();
  void stopTimer();
  void pauseTimer();

  // std::chrono::duration< getTime();
  std::chrono::milliseconds getTime();

 private:
  bool stopped;

  std::chrono::milliseconds startTime;
  std::chrono::milliseconds stopTime;
};

Timer::Timer() : startTime(0), stopTime(0), stopped(true) {}

inline void Timer::startTimer() {
  startTime = std::chrono::milliseconds(Time::getMs());
  stopped = false;
}

inline void Timer::stopTimer() {
  stopTime = std::chrono::milliseconds(Time::getMs());
  stopped = true;
}

inline void Timer::pauseTimer() {
  // paused = true;
}

inline std::chrono::milliseconds Timer::getTime() {
  if (stopped) {
    return stopTime - startTime;
  } else {
    return std::chrono::milliseconds(Time::getMs()) - startTime;
  }
}