
#include "GlContext.h"

GlContext GlContext::context = GlContext();

ShaderProgram& GlContext::activeShader() {
  return *activeShader_;
}

void GlContext::setActiveShader(ShaderProgram& program) {
  activeShader_ = &program;
}
