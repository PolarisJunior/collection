
#include "graphics/gl/GlClient.h"

#include <gl/glew.h>

int32_t GlClient::createShaderProgram(const std::string& vertSource,
                                      const std::string& fragSource) {
  const char* vertexShaderSource = vertSource.c_str();
  const char* fragShaderSource = fragSource.c_str();

  return this->createShaderProgram(vertexShaderSource, fragShaderSource);
}

int32_t GlClient::createShaderProgram(const char* vertSource,
                                      const char* fragSource) {
  int32_t vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderSource = vertSource;

  glShaderSource(vertexShaderHandle, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShaderHandle);

  int32_t success;
  glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &success);
  if (!success) {
    exit(EXIT_FAILURE);
  }

  const char* fragShaderSource = fragSource;
  int32_t fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShaderHandle, 1, &fragShaderSource, nullptr);
  glCompileShader(fragShaderHandle);

  glGetShaderiv(fragShaderHandle, GL_COMPILE_STATUS, &success);
  if (!success) {
    exit(EXIT_FAILURE);
  }

  int32_t programHandle = glCreateProgram();
  glAttachShader(programHandle, vertexShaderHandle);
  glAttachShader(programHandle, fragShaderHandle);
  glLinkProgram(programHandle);

  glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
  if (!success) {
    exit(EXIT_FAILURE);
  }

  glDeleteShader(vertexShaderHandle);
  glDeleteShader(fragShaderHandle);

  return programHandle;
}

uint32_t GlClient::sendMesh(const Mesh& mesh) {
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * mesh.vertices_.size(),
               mesh.vertices_.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(int32_t) * mesh.triangles_.size(), mesh.triangles_.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return VAO;
}