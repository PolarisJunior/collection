
#include "graphics/ShaderProgram.h"
#include <gl/glew.h>
#include <iostream>
#include "graphics/gl/GlContext.h"
#include "io/File.h"

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
  char infoLog[1024];
  if (!success) {
    glGetShaderInfoLog(shaderHandle, 1024, nullptr, infoLog);
    std::cout << "Error: " << infoLog << std::endl;
    exit(EXIT_FAILURE);
  }

  glAttachShader(programHandle, shaderHandle);
  // glDeleteShader(shaderHandle);
  wasLinked = false;
  return shaderHandle;
}

int32_t ShaderProgram::loadVertFromFile(const std::string& filePath) {
  std::string src = File(filePath).readAsString();
  return addVertShader(src);
}

int32_t ShaderProgram::loadFragFromFile(const std::string& filePath) {
  std::string src = File(filePath).readAsString();
  return addFragShader(src);
}

void ShaderProgram::linkProgram() {
  glLinkProgram(programHandle);

  int32_t success;
  glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
  if (!success) {
    exit(EXIT_FAILURE);
  }

  wasLinked = true;
}

void ShaderProgram::useProgram() {
  if (!wasLinked) {
    linkProgram();
  }
  glUseProgram(this->getProgramHandle());
  GlContext::context.setActiveShader(*this);
}

std::optional<ShaderProgram> ShaderProgram::createProgram() {
  int32_t handle = glCreateProgram();
  if (handle) {
    return std::make_optional<ShaderProgram>(handle);
  }
  return std::nullopt;
}

void ShaderProgram::uniform(const std::string& name, const Mat4& m) {
  glUniformMatrix4fv(glGetUniformLocation(getProgramHandle(), name.c_str()), 1,
                     GL_FALSE, m.dataPointer());
}

void ShaderProgram::uniform(const std::string& name, float f) {
  glUniform1f(glGetUniformLocation(getProgramHandle(), name.c_str()), f);
}

void ShaderProgram::uniform(const std::string& name, int32_t v) {
  glUniform1i(glGetUniformLocation(getProgramHandle(), name.c_str()), v);
}