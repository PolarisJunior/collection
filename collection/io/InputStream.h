#pragma once
#include <cstdint>
#include <string>
#include <vector>

class InputStream {
 public:
  InputStream() = default;
  virtual ~InputStream() = default;

  virtual std::vector<char> read(int32_t numBytes) = 0;
  /* Reads one char from the stream */
  virtual char read() = 0;
  virtual bool hasNext() = 0;

  std::string readAsString(int32_t numBytes);
  std::string readAsString();
};
