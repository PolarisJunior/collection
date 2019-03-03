
#pragma once
#include <vector>
#include "../graphics/TileMap.h"
#include "../math/Vector2.h"
// #include "../math/Vector2.h"

class Actor;
class TileMap;
class Renderer;
class Camera2;

class Stage {
 public:
  void setTileMap(const TileMap& tm) { tileMap = tm; }
  void render(Renderer& renderer, Camera2& camera);

 private:
  std::vector<Actor*> actors;
  TileMap tileMap;
  /* Offset of stage or its position in the world */
  Vector2<int32_t> mapOffset;
};
