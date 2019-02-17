
#include "File.h"
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

File::File(const std::string& path) {
  this->pathString = path;
  this->filePath = new std::filesystem::path(this->pathString);
}

File::File(const File& other) : File(other.pathString) {}

File::File(File&& other) {
  swap(*this, other);
}

File::~File() {
  delete this->filePath;
}

int64_t File::getSize() {
  struct stat fileStat;
  if (stat(pathString.c_str(), &fileStat) < 0) {
    return -1;
  } else {
    return fileStat.st_size;
  }
}

std::string File::getExt() {
  std::string ext = filePath->extension().string();
  if (ext[0] == '.') {
    return ext.substr(1);
  } else {
    return ext;
  }
}

bool File::exists() {
  return std::filesystem::exists(*filePath);
}

std::string File::readAsString() {
  static const int32_t bufSize = 4096;
  int64_t fileSize = getSize();
  if (fileSize < 0) {
    return "";
  }
  FILE* f;
  errno_t err;
  if ((err = fopen_s(&f, pathString.c_str(), "rb")) != 0) {
    fprintf(stderr, "could not open %s.\n", pathString.c_str());
    return "";
  }

  char buf[bufSize + 1];

  std::ostringstream ss;
  int64_t bytesLeft = fileSize;
  while (bytesLeft) {
    int64_t bytesRead = fread(&buf, 1, bufSize, f);
    if (bytesRead < bufSize) {
      if (ferror(f) && errno != EINTR) {
        std::cerr << "file read error" << std::endl;
        fclose(f);
        return "";
      }
      clearerr(f);
      buf[bytesRead] = '\0';
      ss << std::string(buf);
      bytesLeft -= bytesRead;
    }
  }

  fclose(f);
  return ss.str();
}

std::vector<std::string> File::readLines() {
  if (!exists()) {
    return std::vector<std::string>();
  }
  std::vector<std::string> res;

  std::ifstream inStream(pathString);
  std::string line;
  while (std::getline(inStream, line)) {
    res.push_back(line);
  }
  return res;
}

std::unique_ptr<char[]> File::readBytes() {
  // static const int32_t bufSize = 4096;
  if (!exists()) {
    return std::unique_ptr<char[]>(nullptr);
  }
  int64_t fileSize = getSize();

  std::ifstream inFile(pathString, std::ifstream::binary);
  char* buf = new char[fileSize];
  std::unique_ptr<char[]> uniq = std::unique_ptr<char[]>(buf);

  inFile.read(buf, fileSize);
  return uniq;
}

File& File::operator=(File other) {
  swap(*this, other);
  return *this;
}

void swap(File& first, File& second) {
  using std::swap;
  swap(first.pathString, second.pathString);
  swap(first.filePath, second.filePath);
}
