
#pragma once

#include <memory>

class Keyboard;
class Mouse;
class GameInstance;

/* Contains data used by instances of a game,
   mostly data that needs to be globally accessed */
class GameInstance {
  std::unique_ptr<Keyboard> kbd;
  std::unique_ptr<Mouse> mouse_;

 public:
  GameInstance();

  Keyboard& keyboard();
  Mouse& mouse();

  /* Gets the current global game instance */
  static GameInstance& instance();

  // TODO init game instance?
  static void initGameInstance();
};
