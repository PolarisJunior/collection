#pragma once

#include <cstdint>
#include "../math/Vector2.h"

class Mouse {
 public:
  Mouse();

  // true if right mouse button down
  bool right();
  bool left();
  bool middle();

  // gets the current mouse screen pos
  Vector2<int32_t> pos();
};