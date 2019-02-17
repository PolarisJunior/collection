
#pragma once
#include <cstdint>
#include <string>

struct SDL_Texture;
class Image;

class Texture {
 public:
  Texture(char* buf, int32_t bufSize, const std::string& type);
  Texture(const Image& image);
  Texture(int32_t w, int32_t h);

  ~Texture();

  SDL_Texture* getSdlTexture();

 private:
  SDL_Texture* sdlTexture;
};

inline SDL_Texture* Texture::getSdlTexture() {
  return sdlTexture;
}
