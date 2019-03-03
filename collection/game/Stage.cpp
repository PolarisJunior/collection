
#include "Stage.h"
#include <algorithm>
#include "../game/Camera2.h"
#include "../graphics/Renderer.h"
#include "../graphics/Texture.h"
#include "../math/geometry/Rect.h"

void Stage::render(Renderer& renderer, Camera2& camera) {
  std::unique_ptr<Texture> tex = tileMap.getTexture();
  if (tex) {
    Vector2 posInScreen = camera.toScreenCoords(Vector2(
        static_cast<float>(mapOffset.x), static_cast<float>(mapOffset.y)));

    Rect<int32_t> dstRect = {posInScreen.x, posInScreen.y, tex->getWidth(),
                             tex->getHeight()};
    renderer.render(*tex, nullptr, &dstRect);
  }
}