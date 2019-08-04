#pragma once

#include <cstdint>

/* Requires events to be pumped to have
valid keyStates */
class Keyboard {
  struct KeyStates {
    const uint8_t* keyStates;
  };

  // Does not need to be free'd
  static KeyStates states;

 public:
  /* true if key, by scanCode, is held down */
  static bool keyDown(uint32_t scanCode);
  static bool keyUp(uint32_t scanCode);

  static void init();

  enum ScanCode {
    Alpha1 = 30,
    Alpha2 = 31,
    Alpha3 = 32,
    Alpha4 = 33,
    Alpha5 = 34,
    Alpha6 = 35,
    Alpha7 = 36,
    Alpha8 = 37,
    Alpha9 = 38,
    Alpha0 = 39
  };
};