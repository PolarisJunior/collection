
#include "GameInstance.h"
#include "../ui/Keyboard.h"
#include "../ui/Mouse.h"

// static or not here?
static GameInstance currentInstance;

GameInstance::GameInstance() {
  this->kbd = std::make_unique<Keyboard>();
}

Keyboard& GameInstance::keyboard() {
  return *this->kbd;
}

Mouse& GameInstance::mouse() {
  return *this->mouse_;
}

GameInstance& GameInstance::instance() {
  return currentInstance;
}
