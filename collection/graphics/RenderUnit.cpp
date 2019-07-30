
#include "RenderUnit.h"
#include "gl/GlClient.h"
#include "gl/glew.h"
#include "graphics/ShaderProgram.h"
#include "graphics/gl/GlContext.h"

RenderUnit::RenderUnit(Mesh&& m) : mesh(std::move(m)) {
  this->vao = GlClient::instance().sendMesh(this->mesh);
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