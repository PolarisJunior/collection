
#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
/* Note we can either use c++ filesystem library or
   low-level sys functions */
namespace std::filesystem {
class path;
}

class File {
 public:
  File() = default;
  File(const std::string& path);
  File(const File& other);
  File(File&& other);
  ~File();

  bool isDir();
  bool makeDir();

  int64_t getSize();

  std::string getExt();

  bool exists();

  bool write(const std::string& dat);
  bool append(const std::string& dat);

  std::string readAsString();
  std::vector<std::string> readLines();
  std::unique_ptr<char[]> readBytes();

  File& operator=(File other);

  friend void swap(File& first, File& second);

 private:
  std::string pathString;
  std::filesystem::path* filePath;
};
