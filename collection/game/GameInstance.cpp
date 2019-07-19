
#include "GameInstance.h"
#include "../ui/Keyboard.h"
#include "../ui/Mouse.h"
#include "./ecs/EntityManager.h"
#include "./ecs/PositionManager.h"

// static or not here?
static GameInstance currentInstance;

GameInstance::GameInstance() {
  this->kbd = std::make_unique<Keyboard>();
  this->mouse_ = std::make_unique<Mouse>();
  this->entityManager_ = std::make_unique<EntityManager>(4096);
  this->posManager_ = std::make_unique<PositionManager>();
}

Keyboard& GameInstance::keyboard() {
  return *this->kbd;
}

Mouse& GameInstance::mouse() {
  return *this->mouse_;
}

EntityManager& GameInstance::entityManager() {
  return *this->entityManager_;
}

PositionManager& GameInstance::posManager() {
  return *this->posManager_;
}

GameInstance& GameInstance::instance() {
  return currentInstance;
}
