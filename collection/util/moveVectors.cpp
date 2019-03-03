
#include "moveVectors.h"

Vector2<float> dirToVecMap[] = {Vector2(0.0f, -1.0f), Vector2(1.0f, 0.0f),
                                Vector2(0.f, 1.f), Vector2(-1.f, 0.f)};

Vector2<float> dirToVec(Direction dir) {
  return dirToVecMap[dir];
}