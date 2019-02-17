
#pragma once
#include <memory>

struct SDL_Renderer;
struct Rect;
struct Color;

class Texture;
class Window;

struct SDL_Texture;
struct SDL_Surface;

struct Renderer {
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

  void drawRect(const Rect& rect);

  void render(Texture& texture, const Rect& src, const Rect& dst);
  void render(Texture& texture, Rect* src, Rect* dst);
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