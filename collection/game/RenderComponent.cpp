
#include "RenderComponent.h"
#include "Actor.h"
#include "RenderSystem.h"
#include "game/Camera.h"
#include "graphics/Color.h"
#include "graphics/Renderer.h"
#include "math/geometry/Rect.h"
#include "ui/Window.h"

void RenderComponent::render(float interpolation) {
  float real_x = attachedActor->x;
  float real_y = attachedActor->y;

  Vector2 screenPos =
      Camera::getMainCamera().toScreenCoords(Vector2(real_x, real_y));

  Rect<int32_t> rect = {static_cast<int32_t>(screenPos.x),
                        static_cast<int32_t>(screenPos.y), 200, 200};
  Renderer& mainRenderer = Window::getMainRenderer();
  mainRenderer.setColor(Colors::WHITE);
  mainRenderer.drawRect(rect);
}

void RenderComponent::onAttached(Actor* actor) {
  renderSystem.registerComponent(this);
}
