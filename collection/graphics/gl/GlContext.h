#pragma once
#include "graphics/ShaderProgram.h"

class GlContext {
 public:
  ShaderProgram& activeShader();
  void setActiveShader(ShaderProgram& shader);

  static GlContext context;

 private:
  ShaderProgram* activeShader_ = nullptr;
};
