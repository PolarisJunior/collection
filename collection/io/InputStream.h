#pragma once
#include <cstdint>

class InputStream {
 public:
  InputStream();
  virtual ~InputStream();

  virtual int32_t read(char* outBuf, int32_t numBytes);

  int32_t readByte(char* out);
};

inline int32_t InputStream::readByte(char* out) {
  return read(out, 1);
}