#pragma once

#include <cstdint>
#include <functional>
#include <queue>
#include "Dir2d.h"

struct ScheduledEvent;

class EventScheduler {
 public:
  void scheduleEvent(void (*f)(), double s);

  void runOnNextTick(std::function<void(void)> f);

  void runUpTo(uint32_t ms);

 private:
  void scheduleEvent(void (*f)(), uint32_t ms);

  std::priority_queue<ScheduledEvent*> scheduledEventQueue;
  std::vector<ScheduledEvent*> awaitingSchedule;
  std::queue<std::function<void(void)>> nextUpdateQueue;
};

extern EventScheduler eventScheduler;