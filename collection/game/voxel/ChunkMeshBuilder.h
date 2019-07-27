#pragma once
#include "Chunk.h"
#include "graphics/models/Mesh.h"

class TextureAtlas;
class BlockDatabase;

class ChunkMeshBuilder {
 public:
  Mesh buildMesh(const Chunk& c, const TextureAtlas& atlas);

 private:
};