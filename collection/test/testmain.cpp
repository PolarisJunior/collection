
#include <SDL.h>
#include <iostream>
#include "../datastructures/Trie.h"
#include "../misc/arrayHopper.h"
#include "../ui/Input.h"
#include "../ui/Window.h"
#include "../ui/WindowBuilder.h"

int test2(int argc, char** argv) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  }

  WindowBuilder windowBuilder;
  windowBuilder.setTitle("fizz buzz").setDims(800, 600);
  Window* window = windowBuilder.getWindow();

  Trie<int32_t> trie;
  printf("%d\n", trie.hasKey("foobar"));

  std::string foo = "hello";
  trie.insert(foo, 5);
  // printf("%d\n", *trie.get(foo));
  printf("has key %d\n", trie.hasKey(foo));
  printf("value: %d\n", *trie.get(foo));

  std::vector<int> arr = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
  auto vec = arrayHop(arr);
  for (auto it = vec.begin(); it < vec.end(); it++) {
    printf("path: %d\n", *it);
  }
  printf("size: %d\n", vec.size());

  printf("keydown: %d\n", Input::getKeyDown("up"));

  SDL_Delay(2000);
  std::cout << "exiting" << std::endl;
  return EXIT_SUCCESS;
}