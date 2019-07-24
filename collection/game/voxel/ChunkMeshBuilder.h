#pragma once
#include "Chunk.h"
#include "graphics/models/Mesh.h"

class ChunkMeshBuilder {
 public:
  static Mesh buildMesh(const Chunk& c);
};