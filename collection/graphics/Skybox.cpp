
#include "Skybox.h"
#include <gl/glew.h>
#include "TextureAtlas.h"
#include "game/Camera.h"
#include "graphics/models/CubeMesh.h"

#ifdef DEBUG
#include <iostream>
#endif

Skybox::Skybox(const std::array<std::string, 6>& faceFiles,
               const std::string& vertFile,
               const std::string& fragFile)
    : shader(ShaderProgram::createProgram()), skyboxRenderer(CubeMesh()) {
#ifdef DEBUG
  std::cout << "Loading Skybox Textures" << std::endl;
#endif
  glGenTextures(1, &cubemapId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);

  for (int i = 0; i < 6; i++) {
    TextureAtlas skyboxFace(faceFiles[i]);
    int32_t format = GL_RGB;
    if (skyboxFace.hasAlpha()) {
      format = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format,
                 skyboxFace.width(), skyboxFace.height(), 0, format,
                 GL_UNSIGNED_BYTE, skyboxFace.dataPointer());
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  shader->loadVertFromFile(vertFile);
  shader->loadFragFromFile(fragFile);

#ifdef DEBUG
  std::cout << "Loaded Skybox" << std::endl;
#endif
}

void Skybox::render() {
  shader->useProgram();
  glFrontFace(GL_CCW);
  glDepthFunc(GL_LEQUAL);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);

  Camera& mainCamera = Camera::getMainCamera();

  Mat4 view = mainCamera.getViewMatrix();
  Mat4 projection = mainCamera.getProjectionMatrix();

  shader->uniform("projection", projection);
  shader->uniform("view", view);

  Transform transform = Transform(mainCamera.transform().worldPosition());
  skyboxRenderer.render(transform);

  glFrontFace(GL_CW);
  glDepthFunc(GL_LESS);
}

// float skyboxVertices[] = {
//     // positions
//     -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
//     1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

//     -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
//     -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

//     1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

//     -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

//     -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

//     -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
//     1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};
// unsigned int skyboxVAO, skyboxVBO;
// glGenVertexArrays(1, &skyboxVAO);
// glGenBuffers(1, &skyboxVBO);
// glBindVertexArray(skyboxVAO);
// glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
// glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices,
//              GL_STATIC_DRAW);
// glEnableVertexAttribArray(0);
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
// (void*)0);

// glDrawArrays(GL_TRIANGLES, 0, 36);
// glDrawElements(GL_TRIANGLES, skyboxRenderUnit.mesh.triangles().size(),
//                GL_UNSIGNED_INT, 0);
// glDepthMask(GL_TRUE);