
#include "RenderComponent.h"
#include "../graphics/Color.h"
#include "../graphics/Renderer.h"
#include "../math/geometry/Rect.h"
#include "RenderSystem.h"

void RenderComponent::render(float interpolation) {
  Rect rect = {100, 100, 200, 200};
  mainRenderer.setColor(Colors::WHITE);
  mainRenderer.drawRect(rect);
}

void RenderComponent::onAttached(Actor* actor) {
  renderSystem.registerComponent(this);
}
