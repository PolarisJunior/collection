#pragma once
#include "graphics/models/Mesh.h"

class PlaneMesh : public Mesh {
 public:
  PlaneMesh() : Mesh(planeVertices, planeTriangles, planeUvs, planeNormals) {}

  inline static const std::vector<Vec3> planeVertices = {
      Vec3(-.5, 0, .5), Vec3(.5, 0, .5), Vec3(-.5, 0, -.5), Vec3(.5, 0, -.5)};

  inline static const std::vector<int32_t> planeTriangles = {0, 1, 2, 1, 3, 2};

  inline static const std::vector<Vec2> planeUvs = {Vec2(1, 0), Vec2(0, 0),
                                                    Vec2(1, 1), Vec2(0, 1)};
  inline static const std::vector<Vec3> planeNormals = {
      Vec3(0, 1, 0), Vec3(0, 1, 0), Vec3(0, 1, 0), Vec3(0, 1, 0)};
};