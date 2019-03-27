#pragma once

#include <cstdint>

/* Requires events to be pumped to have
valid keyStates */
class Keyboard {
  // Does not need to be free'd
  const uint8_t* keyStates;

 public:
  Keyboard();

  /* true if key, by scanCode, is held down */
  bool keyDown(uint32_t scanCode);
  bool keyUp(uint32_t scanCode);
};