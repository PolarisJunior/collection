#pragma once

#include <array>
#include <cstdint>
#include "../math/Vector2.h"

class Mouse {
 public:
  Mouse() = default;

  // true if right mouse button down
  static bool right();
  static bool left();
  static bool middle();

  // returns true on the frame button is down
  // TODO what happens if down and up in same frame?
  static bool buttonDown(int32_t button);
  static bool buttonUp(int32_t button);

  static void update();

  // gets the current mouse screen pos
  static Vector2<int32_t> pos();

  enum class Button { LEFT = 0, RIGHT = 1, MIDDLE = 2 };

  inline static std::array<Button, 3> buttons = {Button::LEFT, Button::RIGHT,
                                                 Button::MIDDLE};
  inline static std::array<bool, 3> downThisFrame = {false, false, false};
  inline static std::array<bool, 3> upThisFrame = {false, false, false};
};