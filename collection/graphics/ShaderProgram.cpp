
#include "graphics/ShaderProgram.h"
#include <gl/glew.h>
#include <iostream>

ShaderProgram::ShaderProgram(int32_t handle) : programHandle(handle) {}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(programHandle);
}

int32_t ShaderProgram::addVertShader(const std::string& src) {
  return this->addShader(src, ShaderType::VERTEX);
}

int32_t ShaderProgram::addFragShader(const std::string& src) {
  return this->addShader(src, ShaderType::FRAGMENT);
}

int32_t ShaderProgram::addShader(const std::string& src, ShaderType type) {
  int32_t shaderHandle;
  switch (type) {
    case ShaderType::VERTEX:
      shaderHandle = glCreateShader(GL_VERTEX_SHADER);
      break;
    case ShaderType::FRAGMENT:
      shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
      break;
  }

  const char* cSrc = src.c_str();

  glShaderSource(shaderHandle, 1, &cSrc, nullptr);
  glCompileShader(shaderHandle);

  int32_t success;
  glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
  if (!success) {
    exit(EXIT_FAILURE);
  }

  glAttachShader(programHandle, shaderHandle);
  // glDeleteShader(shaderHandle);
}

void ShaderProgram::finalizeProgram() {
  glLinkProgram(programHandle);

  int32_t success;
  glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
  if (!success) {
    exit(EXIT_FAILURE);
  }
}

void ShaderProgram::useProgram() {
  glUseProgram(this->getProgramHandle());
}

std::optional<ShaderProgram> ShaderProgram::createProgram() {
  int32_t handle = glCreateProgram();
  if (handle) {
    return std::make_optional<ShaderProgram>(handle);
  }
  return std::nullopt;
}

void ShaderProgram::uniform(const std::string& name, Mat4& m) {
  glUniformMatrix4fv(glGetUniformLocation(getProgramHandle(), name.c_str()), 1,
                     GL_FALSE, m.dataPointer());
}

void ShaderProgram::uniform(const std::string& name, float f) {
  glUniform1f(glGetUniformLocation(getProgramHandle(), name.c_str()), f);
}