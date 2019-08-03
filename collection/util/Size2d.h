#pragma once

template <typename T>
class Size2d {
 public:
  void width(T& w) { width_ = w; }
  void height(T& h) { height_ = h; }

  T width() const { return width_; };
  T height() const { return height_; };

  T area() const { return width_ * height_; }

 protected:
  T width_;
  T height_;
};
