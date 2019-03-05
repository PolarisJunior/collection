#pragma once
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include "InputStream.h"

class File;

class FileInputStream : public InputStream {
 public:
  FileInputStream(FileInputStream&& other);
  ~FileInputStream();

  std::vector<char> read(int32_t numBytes) override;
  char read() override;
  bool hasNext() override;
  std::string readLine() override;

  /* Use this to get stream objects */
  static std::optional<FileInputStream> getStream(const std::string& filePath);

 private:
  std::unique_ptr<File> actualFile;
  std::unique_ptr<std::ifstream> stream;

  FileInputStream(const std::string& filePath);
};
