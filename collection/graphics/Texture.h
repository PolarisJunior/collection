
#pragma once
#include <cstdint>
#include <string>

struct SDL_Texture;
class Image;

class Texture {
 public:
  Texture(char* buf, int32_t bufSize, const std::string& type = "png");
  Texture(const Image& image);
  Texture(const std::string& filePath);
  Texture(int32_t w, int32_t h);

  ~Texture();

  SDL_Texture* getSdlTexture();

  int32_t getWidth();
  int32_t getHeight();

 private:
  SDL_Texture* sdlTexture;

  int32_t width;
  int32_t height;
};

inline SDL_Texture* Texture::getSdlTexture() {
  return sdlTexture;
}

inline int32_t Texture::getWidth() {
  return width;
}

inline int32_t Texture::getHeight() {
  return height;
}