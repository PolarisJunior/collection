
#pragma once
#include <sys/stat.h>
#include <cstdint>
#include <filesystem>
#include <string>
/* Note we can either use c++ filesystem library or
   low-level sys functions */

class File {
 public:
  File(const std::string& filePath);
  ~File() = default;

  bool isDir();
  bool makeDir();

  int64_t getSize();

  bool exists();

  bool write(const std::string& dat);
  bool append(const std::string& dat);

  std::string readString();
  std::string readLine();

 private:
  std::string path;
};

File::File(const std::string& filePath) {
  this->path = filePath;
}

/* Get file size or returns -1 if file does not exist */
int64_t File::getSize() {
  struct stat fileStat;
  if (stat(path.c_str(), &fileStat) < 0) {
    return -1;
  } else {
    return fileStat.st_size;
  }
}

bool File::exists() {
  std::filesystem::path p(path);
  return std::filesystem::exists(p);
}
