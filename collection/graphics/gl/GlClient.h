#pragma once

#include <string>
#include <utility>
#include <vector>
#include "graphics/models/Mesh.h"

class GlClient {
 public:
  int32_t createShaderProgram(const std::string& vertSource,
                              const std::string& fragSource);

  int32_t createShaderProgram(const char* vertSource, const char* fragSource);

  // uint32_t sendMesh(const Mesh& mesh);
  std::pair<uint32_t, std::vector<uint32_t>> sendMesh(const Mesh& mesh);

  void setClearColor(float r, float g, float b, float a);

  void clearAllBuffers();

  static GlClient& instance();

 private:
  static GlClient client;
};