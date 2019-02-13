
#pragma once
#include <SDL.h>
#include <string>

class Input {
 public:
  static bool getKey(const std::string& key);
  static bool getKeyDown(const std::string& key);
  static bool getKeyUp(const std::string& key);

  static void recordEvent();

  static void keyDownListener();
  static void keyUpListener();

 private:
};