
#include "Keyboard.h"
#include <SDL.h>
#include <set>

Keyboard::KeyStates Keyboard::states;

std::array<bool, Keyboard::NUM_SCANCODES> Keyboard::keys_pressed = {0};

static std::set<uint32_t> pressed_keys_to_reset;
static std::set<uint32_t> released_keys_to_reset;

void Keyboard::init() {
  states = KeyStates{SDL_GetKeyboardState(nullptr)};
}

void Keyboard::Update() {
  for (uint32_t key_index : pressed_keys_to_reset) {
    keys_pressed[key_index] = false;
  }
  pressed_keys_to_reset.clear();
}

bool Keyboard::keyDown(uint32_t scanCode) {
  return states.keyStates[scanCode];
}

bool Keyboard::keyUp(uint32_t scanCode) {
  return !keyDown(scanCode);
}

bool Keyboard::KeyPressed(uint32_t scan_code) {
  return keys_pressed[scan_code];
}

void Keyboard::NotifyKeyPressed(uint32_t scan_code) {
  pressed_keys_to_reset.insert(scan_code);
  keys_pressed[scan_code] = true;
}

bool Keyboard::KeyReleased(uint32_t scan_code) {
  return false;
}
bool Keyboard::NotifyKeyReleased(uint32_t scan_code) {
  return false;
}