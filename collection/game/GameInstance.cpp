
#include "GameInstance.h"
#include "../ui/Keyboard.h"

// static or not here?
static GameInstance currentInstance;

GameInstance::GameInstance() {
  this->kbd = std::make_unique<Keyboard>();
}

Keyboard& GameInstance::keyboard() {
  return *this->kbd;
}

GameInstance& GameInstance::instance() {
  return currentInstance;
}
