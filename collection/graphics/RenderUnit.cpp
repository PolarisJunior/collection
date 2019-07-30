
#include "RenderUnit.h"
#include "gl/GlClient.h"
#include "gl/glew.h"
#include "graphics/ShaderProgram.h"

RenderUnit::RenderUnit(Mesh&& m) : mesh(std::move(m)) {
  this->vao = GlClient::instance().sendMesh(this->mesh);
}

void RenderUnit::render(Transform& transform) {
  // prog->uniform("model", transform.getModelMatrix());
  // prog->uniform("model_normal", transform.localRotation().toMatrix());
}