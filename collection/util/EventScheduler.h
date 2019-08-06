#pragma once

#include <cstdint>
#include <functional>
#include <queue>

struct ScheduledEvent;

class EventScheduler {
 public:
  static void scheduleEvent(void (*f)(), double s);

  static void runOnNextTick(std::function<void(void)> f);

  static void runUpTo(uint32_t ms);
  static void runUpTo(double t);

 private:
  static void scheduleEvent(void (*f)(), uint32_t ms);

  inline static std::priority_queue<ScheduledEvent*> scheduledEventQueue;
  inline static std::vector<ScheduledEvent*> awaitingSchedule;
  inline static std::queue<std::function<void(void)>> nextUpdateQueue;
};

extern EventScheduler eventScheduler;