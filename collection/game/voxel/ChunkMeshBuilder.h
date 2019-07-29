#pragma once
#include "Chunk.h"
#include "graphics/TextureAtlas.h"
#include "graphics/models/Mesh.h"

class TextureAtlas;
class BlockDatabase;

class ChunkMeshBuilder {
 public:
  ChunkMeshBuilder(const TextureAtlas& a) : atlas(a) {}

  Mesh buildMesh(const Chunk& c) const;

 private:
  const TextureAtlas& atlas;
};