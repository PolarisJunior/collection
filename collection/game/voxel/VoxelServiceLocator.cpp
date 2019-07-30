
#include "VoxelServiceLocator.h"
#include "TerrainGenerator.h"

VoxelServiceLocator VoxelServiceLocator::locator = VoxelServiceLocator();

VoxelServiceLocator::VoxelServiceLocator()
    : terrainGenerator_(std::make_unique<TerrainGenerator>()) {}

TerrainGenerator& VoxelServiceLocator::terrainGenerator() {
  return *terrainGenerator_;
}

VoxelServiceLocator& VoxelServiceLocator::instance() {
  return locator;
}