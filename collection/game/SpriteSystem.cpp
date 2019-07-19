
#include "SpriteSystem.h"
#include "../graphics/Sprite.h"
#include "Actor.h"

SpriteSystem spriteSystem;

void SpriteSystem::registerComponent(Sprite* sprite) {
  registered.push_back(sprite);
}

void SpriteSystem::renderAll(float interp) {
  for (auto it = registered.begin(); it < registered.end(); it++) {
    Sprite* sprite = *it;
    if (sprite->isAttached()) {
    }
  }
}