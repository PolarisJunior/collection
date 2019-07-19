#pragma once
#include <vector>

class Sprite;

class SpriteSystem {
 public:
  void registerComponent(Sprite* sprite);
  void unRegisterComponent(Sprite* sprite);
  void renderAll(float interp);

 private:
  std::vector<Sprite*> registered;
};

extern SpriteSystem spriteSystem;