
#include "RenderUnit.h"
#include "gl/GlClient.h"
#include "gl/glew.h"
#include "graphics/ShaderProgram.h"
#include "graphics/gl/GlContext.h"

RenderUnit::RenderUnit(Mesh&& m) : mesh(std::move(m)) {
  std::pair<uint32_t, std::vector<uint32_t>> res =
      GlClient::instance().sendMesh(this->mesh);

  this->vao = res.first;
  this->bufferIds = res.second;
}

RenderUnit::RenderUnit(RenderUnit&& u)
    : mesh(std::move(u.mesh)),
      vao(u.vao),
      bufferIds(u.bufferIds.begin(), u.bufferIds.end()) {
  u.vao = 0;
  u.bufferIds.clear();
}

RenderUnit::~RenderUnit() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(bufferIds.size(), bufferIds.data());
}

RenderUnit& RenderUnit::operator=(RenderUnit&& other) {
  if (this != &other) {
    mesh = std::move(other.mesh);
    vao = other.vao;
    bufferIds = std::move(other.bufferIds);

    other.bufferIds.clear();
    other.vao = 0;
  }
  return *this;
}

void RenderUnit::render(Transform& transform) {
  ShaderProgram& prog = GlContext::context.activeShader();
  prog.uniform("model", transform.getModelMatrix());
  prog.uniform("model_normal", transform.localRotation().toMatrix());

  glBindVertexArray(this->vao);
  glDrawElements(GL_TRIANGLES, mesh.triangles().size(), GL_UNSIGNED_INT, 0);
}
// setup deletion later
// glDeleteVertexArrays(1, &vao2);