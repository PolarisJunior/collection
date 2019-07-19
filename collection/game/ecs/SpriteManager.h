#pragma once

#include "../../graphics/Texture.h"
#include "../Camera2.h"
#include "ComponentManager.h"
#include "PositionManager.h"

// struct Sprite {
//   Texture& texture;
// };

class SpriteManager : public ComponentManager<Texture> {
  PositionManager& positionManager;
  Camera2& camera;

 public:
  SpriteManager(PositionManager& pManager, Camera2& cam)
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
