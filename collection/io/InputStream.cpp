
#include "InputStream.h"

#include <sstream>

std::string InputStream::readAsString(int32_t numBytes) {
  std::stringstream ss;
  while (hasNext() && numBytes > 0) {
    ss << read();
    numBytes--;
  }
  return ss.str();
}

std::string InputStream::readAsString() {
  std::stringstream ss;

  while (hasNext()) {
    ss << read();
  }

  return ss.str();
}