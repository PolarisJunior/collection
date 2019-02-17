
#include "Image.h"
#include "../io/File.h"

Image::Image(const std::string& filePath) {
  File file(filePath);
  buf = file.readBytes();
  bufSize = file.getSize();
  type = file.getExt();
}

std::string Image::getType() const {
  return type;
}

uint32_t Image::getImageSize() const {
  return bufSize;
}