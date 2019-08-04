
#include "Keyboard.h"
#include <SDL.h>

Keyboard::KeyStates Keyboard::states;

void Keyboard::init() {
  states = KeyStates{SDL_GetKeyboardState(nullptr)};
}

bool Keyboard::keyDown(uint32_t scanCode) {
  return states.keyStates[scanCode];
}

bool Keyboard::keyUp(uint32_t scanCode) {
  return !keyDown(scanCode);
}