
#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

class Image {
 public:
  Image(const std::string& filePath);

  uint32_t getImageSize() const;
  std::string getType() const;

  std::unique_ptr<char[]> buf;

 private:
  std::string type;
  uint32_t bufSize;
};