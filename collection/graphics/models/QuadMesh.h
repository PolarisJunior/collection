#pragma once
#include "graphics/models/Mesh.h"

class QuadMesh : public Mesh {
 public:
  QuadMesh() : Mesh(quadVertices, quadTriangles, quadUvs, quadNormals) {}

  inline static const std::vector<Vec3> quadVertices = {
      Vec3(-.5, 0, .5), Vec3(.5, 0, .5), Vec3(-.5, 0, -.5), Vec3(.5, 0, -.5)};

  inline static const std::vector<int32_t> quadTriangles = {0, 1, 2, 1, 3, 2};

  inline static const std::vector<Vec2> quadUvs = {Vec2(1, 0), Vec2(0, 0),
                                                   Vec2(1, 1), Vec2(0, 1)};
  inline static const std::vector<Vec3> quadNormals = {
      Vec3(0, 1, 0), Vec3(0, 1, 0), Vec3(0, 1, 0), Vec3(0, 1, 0)};
};