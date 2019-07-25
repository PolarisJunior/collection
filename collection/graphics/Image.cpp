
#include "Image.h"
#include <iostream>
#include "io/File.h"

Image::Image(const std::string& filePath) {
  std::cout << "is this ever run" << std::endl;
  File file(filePath);
  buf = file.readBytes();
  bufSize = file.getSize();
  type = file.getExt();
}

std::string Image::getType() const {
  return type;
}

int64_t Image::getImageSize() const {
  return bufSize;
}