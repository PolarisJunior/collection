
#include "graphics/gl/GlClient.h"

#include <gl/glew.h>

GlClient GlClient::client = GlClient();

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
std::pair<uint32_t, std::vector<uint32_t>> GlClient::sendMesh(
    const Mesh& mesh) {
  uint32_t VBO, VAO, EBO, UV, NORMS;
  glGenVertexArrays(1, &VAO);

  std::vector<uint32_t> buffers(4);
  glGenBuffers(4, buffers.data());

  VBO = buffers[0];
  EBO = buffers[1];
  UV = buffers[2];
  NORMS = buffers[3];

  glBindVertexArray(VAO);

  // UVS
  glBindBuffer(GL_ARRAY_BUFFER, UV);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * mesh.uvs().size(),
               mesh.uvs().data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);

  // NORMALS
  glBindBuffer(GL_ARRAY_BUFFER, NORMS);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * mesh.normals().size(),
               mesh.normals().data(), GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(2);

  // POSITIONS

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * mesh.vertices().size(),
               mesh.vertices().data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // INDICES/TRIANGLES
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(int32_t) * mesh.triangles().size(),
               mesh.triangles().data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return std::make_pair(VAO, buffers);
}

void GlClient::setClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void GlClient::clearAllBuffers() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

GlClient& GlClient::instance() {
  return GlClient::client;
}