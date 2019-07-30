#pragma once

#include <memory>

class TerrainGenerator;

class VoxelServiceLocator {
 public:
  VoxelServiceLocator();

  TerrainGenerator& terrainGenerator();

  std::unique_ptr<TerrainGenerator> terrainGenerator_;

  static VoxelServiceLocator& instance();
  static VoxelServiceLocator locator;
};