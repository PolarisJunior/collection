
#include "loaders/SdlLoader.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

std::pair<bool, std::string> SdlLoader::load() {
  std::string msg;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    msg = std::string(SDL_GetError());
    goto fail;
  }
  {
    uint32_t flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if (IMG_Init(flags) != flags) {
      msg = std::string(IMG_GetError());
      goto fail;
    }
  }
  {
    if (TTF_Init() != 0) {
      msg = std::string(TTF_GetError());
      goto fail;
    }
  }
  return std::pair(true, msg);
fail:
  return std::pair(false, msg);
}