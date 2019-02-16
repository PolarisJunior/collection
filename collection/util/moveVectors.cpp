
#include "moveVectors.h"

Vector2 dirToVecMap[] = {Vector2(0, -1), Vector2(1, 0), Vector2(0, 1),
                         Vector2(-1, 0)};

Vector2 dirToVec(Direction dir) {
  return dirToVecMap[dir];
}