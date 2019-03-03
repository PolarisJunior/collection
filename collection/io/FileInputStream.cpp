
#include "FileInputStream.h"
#include <cstdio>
#include <fstream>
#include "File.h"

FileInputStream::FileInputStream(const std::string& filePath) {
  actualFile = std::make_unique<File>(filePath);
  stream = std::make_unique<std::ifstream>(filePath);
}

FileInputStream::~FileInputStream() {}

std::vector<char> FileInputStream::read(int32_t numBytes) {
  std::vector<char> out;

  while (hasNext() && numBytes > 0) {
    out.push_back(read());
    numBytes--;
  }

  return out;
}

char FileInputStream::read() {
  return stream->get();
}

bool FileInputStream::hasNext() {
  return !stream->eof();
}

std::optional<FileInputStream> FileInputStream::getStream(
    const std::string& filePath) {
  File file(filePath);
  if (file.exists()) {
    return std::optional<FileInputStream>(filePath);
  }
  return {};
}
