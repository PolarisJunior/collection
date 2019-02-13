#pragma once
#include <stdio.h>
#include "InputStream.h"

class FileInputStream : public InputStream {
 public:
  FileInputStream(FILE* file);
  ~FileInputStream();

 private:
};