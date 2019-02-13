
#pragma once
#include <cstdint>

class Actor;

enum ComponentId { UNDEFINED, RENDERABLE };

class Component {
 public:
  const int32_t componentId = ComponentId::UNDEFINED;
  void attachToActor(Actor* actor, bool notify = true);

  virtual void onAttached();
  virtual void onUnattached();

  // virtual void update();

 private:
  Actor* attachedActor;
};