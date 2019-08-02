#pragma once
#include <array>
#include <string>
#include "graphics/RenderUnit.h"
#include "graphics/ShaderProgram.h"

class Skybox {
 public:
  Skybox(const std::array<std::string, 6>& faceFiles,
         const std::string& vertFile,
         const std::string& fragFile);

  void render();

 private:
  uint32_t cubemapId;
  std::optional<ShaderProgram> shader;

  RenderUnit skyboxRenderer;
};
