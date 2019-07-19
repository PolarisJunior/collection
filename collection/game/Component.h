
#pragma once
#include <cstdint>

class Actor;

class Component {
 public:
  /* attaches self to an actor, if notify is true, actor
      also becomes aware of the component */
  void attachToActor(Actor* actor, bool notify = true);

  /* What to do when attached to actor */
  virtual void onAttached(Actor* actor);
  /* What to do when unattached from actor */
  virtual void onUnattached(Actor* actor);

  bool isAttached() { return attachedActor != nullptr; }

  // virtual void update();
 protected:
  Actor* attachedActor;
};
