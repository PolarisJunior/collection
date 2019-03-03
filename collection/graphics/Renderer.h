
#pragma once
#include <memory>

struct SDL_Renderer;
template <typename T>
struct Rect;
struct Color;

class Texture;
class Window;

struct SDL_Texture;
struct SDL_Surface;

class Renderer {
 public:
  Renderer() = default;
  Renderer(SDL_Renderer* r);
  Renderer(Window& window);
  Renderer(Renderer&& other);
  ~Renderer();

  void present();
  void clear();

  void setColor(const Color& color);
  void setTarget(Texture& texture);
  void clearTarget();

  void drawRect(const Rect<int32_t>& rect);

  void render(Texture& texture,
              const Rect<int32_t>& src,
              const Rect<int32_t>& dst);
  void render(Texture& texture, Rect<int32_t>* src, Rect<int32_t>* dst);
  void render(Texture& texture);

  SDL_Renderer* getSdlRenderer();

  SDL_Texture* createTextureFromSurface(SDL_Surface* surface);

  // which should we use?
  Renderer& operator=(Renderer other);
  // Renderer& operator=(Renderer&& other);

  friend void swap(Renderer& first, Renderer& second);

 private:
  SDL_Renderer* sdlRenderer;
};

inline Renderer::Renderer(SDL_Renderer* r) {
  sdlRenderer = r;
}

inline SDL_Renderer* Renderer::getSdlRenderer() {
  return sdlRenderer;
}

extern Renderer mainRenderer;