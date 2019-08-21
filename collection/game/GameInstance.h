
#pragma once

#include <atomic>
#include <memory>

class GameInstance {
 public:
  // The game is currently running and processing updates
  inline static std::atomic_bool isRunning = false;
};
