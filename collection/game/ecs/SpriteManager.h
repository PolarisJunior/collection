#pragma once

#include "game/Camera.h"
#include "game/ecs/ComponentManager.h"
#include "game/ecs/PositionManager.h"
#include "graphics/Texture.h"

// struct Sprite {
//   Texture& texture;
// };

class SpriteManager : public ComponentManager<Texture> {
  PositionManager& positionManager;
  Camera& camera;

 public:
  SpriteManager(PositionManager& pManager, Camera& cam)
      : positionManager(pManager), camera(cam) {}

  void renderAll(float interpolation) {
    for (auto& pair : entityToComp) {
      uint32_t eid = pair.first;
      uint32_t cid = pair.second;

      if (positionManager.isRegistered(eid)) {
        Vector2<float> vec =
            camera.toScreenCoords(positionManager.getPosition(eid));
        dataArray[cid].render(vec.x, vec.y);
      }
    }
  }
};
