#pragma once

#include <array>
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
  static constexpr int32_t NUM_SCANCODES = 512;
  /* true if key, by scanCode, is held down */
  static bool keyDown(uint32_t scanCode);
  static bool keyUp(uint32_t scanCode);

  // True if key was pressed in this frame
  static bool KeyPressed(uint32_t scan_code);
  static void NotifyKeyPressed(uint32_t scan_code);

  static bool KeyReleased(uint32_t scan_code);
  static bool NotifyKeyReleased(uint32_t scan_code);

  static void init();
  static void Update();

  enum ScanCode {
    M = 16,
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

 private:
  static std::array<bool, NUM_SCANCODES> keys_pressed;
};