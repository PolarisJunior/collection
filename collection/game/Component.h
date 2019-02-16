
#pragma once
#include <cstdint>

class Actor;

enum ComponentId { UNDEFINED, RENDERABLE };

class Component {
 public:
  const int32_t componentId = ComponentId::UNDEFINED;
  void attachToActor(Actor* actor, bool notify = true);

  virtual void onAttached(Actor* actor);
  virtual void onUnattached(Actor* actor);

  // virtual void update();

 protected:
  Actor* attachedActor;
};