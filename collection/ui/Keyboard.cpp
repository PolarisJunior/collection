
#include "Keyboard.h"
#include <SDL.h>

Keyboard::Keyboard() {
  keyStates = SDL_GetKeyboardState(nullptr);
}

bool Keyboard::keyDown(uint32_t scanCode) {
  return keyStates[scanCode];
}

bool Keyboard::keyUp(uint32_t scanCode) {
  return !keyDown(scanCode);
}