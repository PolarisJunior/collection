#pragma once

#include "Mesh.h"

class CubeMesh : public Mesh {
 public:
  CubeMesh() : Mesh() {
    vertices_ = cubeVertices;
    triangles_ = cubeTriangles;
    uvs_ = cubeUvs;
  }

  static const std::vector<Vec3> cubeVertices;

  inline static const std::vector<Vec2> cubeUvs = {
      Vec2(0, 0), Vec2(1, 0), Vec2(0, 1), Vec2(1, 1), Vec2(0, 1), Vec2(1, 1),
      Vec2(0, 1), Vec2(1, 1), Vec2(0, 0), Vec2(1, 0), Vec2(0, 0), Vec2(1, 0),
      Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0), Vec2(0, 0), Vec2(0, 1),
      Vec2(1, 1), Vec2(1, 0), Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0)};

  static const std::vector<int32_t> cubeTriangles;
  // inline static const std::vector<int32_t> cubeTriangles = {
  //     0,  2,  3,  0,  3,  1,  8,  4,  5,  8,  5,  9,  10, 6,  7,  10, 7,  11,
  //     12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22,
  //     23};
};
