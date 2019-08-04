#pragma once

#include <cstdint>
#include "../math/Vector2.h"

class Mouse {
 public:
  Mouse() = default;

  // true if right mouse button down
  static bool right();
  static bool left();
  static bool middle();

  // gets the current mouse screen pos
  static Vector2<int32_t> pos();

  enum class Button { LEFT = 0, RIGHT = 1, MIDDLE = 2 };
};