
#pragma once
#include <cstdint>
#include <memory>
#include <string>

class Image {
 public:
  Image(const std::string& filePath);

  uint32_t getImageSize() const;
  std::string getType() const;

  std::unique_ptr<char[]> buf;
  uint32_t bufSize;

 private:
  std::string type;
};