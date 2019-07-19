
#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

class Image {
 public:
  Image(const std::string& filePath);

  int64_t getImageSize() const;
  std::string getType() const;

  std::unique_ptr<char[]> buf;

 private:
  std::string type;
  int64_t bufSize;
};