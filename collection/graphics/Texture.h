
#pragma once
#include <cstdint>
#include <string>

struct SDL_Texture;
class Image;

class Texture {
 public:
  Texture(char* buf, int32_t bufSize, const std::string& type);
  Texture(const Image& image);
  ~Texture();
  SDL_Texture* sdlTexture;

 private:
};
