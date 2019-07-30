
#include "RenderActor.h"

RenderActor::RenderActor(RenderUnit&& unit, const Transform& t)
    : renderUnit(std::move(unit)) {
  transform = t;
}

RenderActor::RenderActor(Mesh&& mesh, const Transform& t)
    : RenderActor(RenderUnit(std::move(mesh)), t) {}

void RenderActor::render() {
  renderUnit.render(transform);
}