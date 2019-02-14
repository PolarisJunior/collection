
#pragma once

struct SDL_Renderer;
struct Rect;
struct Color;

struct Renderer {
 public:
  Renderer() = default;
  Renderer(SDL_Renderer* r);

  void present();
  void clear();

  void setColor(const Color& color);

  void drawRect(const Rect& rect);

  SDL_Renderer* sdlRenderer;
};

inline Renderer::Renderer(SDL_Renderer* r) {
  sdlRenderer = r;
}

extern Renderer mainRenderer;