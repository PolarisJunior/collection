
#include "EventScheduler.h"
#include "time/Time.h"
#include "units.h"

struct ScheduledEvent {
  ScheduledEvent(void (*f)(), uint32_t ms);
  void (*func)();
  /* Time this will run presumably in ms */
  uint32_t timeToRun;

  inline friend bool operator<(const ScheduledEvent& lhs,
                               const ScheduledEvent& rhs);
};

ScheduledEvent::ScheduledEvent(void (*f)(), uint32_t ms)
    : func(f), timeToRun(ms) {}

bool operator<(const ScheduledEvent& lhs, const ScheduledEvent& rhs) {
  return lhs.timeToRun > rhs.timeToRun;
}

void EventScheduler::scheduleEvent(void (*f)(), double s) {
  scheduleEvent(f, secondsToMs(s));
}

/* TODO find a non intrusive way to put these on the stack */
void EventScheduler::scheduleEvent(void (*f)(), uint32_t ms) {
  ScheduledEvent* event = new ScheduledEvent(f, ms + Time::getMs());
  scheduledEventQueue.push(event);
}

void EventScheduler::runOnNextTick(std::function<void(void)> f) {
  nextUpdateQueue.push(f);
}

void EventScheduler::runUpTo(uint32_t ms) {
  while (!scheduledEventQueue.empty() &&
         scheduledEventQueue.top()->timeToRun < ms) {
    scheduledEventQueue.top()->func();
    delete scheduledEventQueue.top();
    scheduledEventQueue.pop();
  }
}