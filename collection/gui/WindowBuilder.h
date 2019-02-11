#pragma once

#include <string>

class Window;

class WindowBuilder {
 public:
  WindowBuilder();

  WindowBuilder& setTitle(const std::string& title);

  WindowBuilder& setWidth(int w);
  WindowBuilder& setHeight(int h);
  WindowBuilder& setDims(int w, int h);

  WindowBuilder& setPos(int x, int y);

  WindowBuilder& setFlags(uint32_t flags);

  Window* getWindow();

 private:
  std::string title = "untitled";

  int width = 800;
  int height = 600;

  int xPos;
  int yPos;

  uint32_t flags;
};