#pragma once

#include "Mesh.h"

class CubeMesh : public Mesh {
 public:
  CubeMesh() : Mesh(cubeVertices, cubeTriangles, cubeUvs, cubeNormals) {
    // vertices_ = cubeVertices;
    // triangles_ = cubeTriangles;
    // uvs_ = cubeUvs;
  }

  // Notice how we can make these static const or inline static const

  static const std::vector<Vec3> cubeVertices;

  inline static const std::vector<Vec2> cubeUvs = {
      Vec2(0, 0), Vec2(1, 0), Vec2(0, 1), Vec2(1, 1), Vec2(0, 1), Vec2(1, 1),
      Vec2(0, 1), Vec2(1, 1), Vec2(0, 0), Vec2(1, 0), Vec2(0, 0), Vec2(1, 0),
      Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0), Vec2(0, 0), Vec2(0, 1),
      Vec2(1, 1), Vec2(1, 0), Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0)};
  inline static const std::vector<Vec3> cubeNormals = {
      Vec3(0, 0, 1),  Vec3(0, 0, 1),  Vec3(0, 0, 1),  Vec3(0, 0, 1),
      Vec3(0, 1, 0),  Vec3(0, 1, 0),  Vec3(0, 0, -1), Vec3(0, 0, -1),
      Vec3(0, 1, 0),  Vec3(0, 1, 0),  Vec3(0, 0, -1), Vec3(0, 0, -1),
      Vec3(0, -1, 0), Vec3(0, -1, 0), Vec3(0, -1, 0), Vec3(0, -1, 0),
      Vec3(-1, 0, 0), Vec3(-1, 0, 0), Vec3(-1, 0, 0), Vec3(-1, 0, 0),
      Vec3(1, 0, 0),  Vec3(1, 0, 0),  Vec3(1, 0, 0),  Vec3(1, 0, 0)};
  static const std::vector<int32_t> cubeTriangles;
  // inline static const std::vector<int32_t> cubeTriangles = {
  //     0,  2,  3,  0,  3,  1,  8,  4,  5,  8,  5,  9,  10, 6,  7,  10, 7,  11,
  //     12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22,
  //     23};
};
