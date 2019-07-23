#pragma once

#include <string>
#include "graphics/models/Mesh.h"

class GlClient {
 public:
  int32_t createShaderProgram(const std::string& vertSource,
                              const std::string& fragSource);

  int32_t createShaderProgram(const char* vertSource, const char* fragSource);

  uint32_t sendMesh(const Mesh& mesh);
};