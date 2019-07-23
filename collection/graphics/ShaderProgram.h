#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include "math/Mat4.h"

class ShaderProgram {
 public:
  enum class ShaderType { VERTEX, FRAGMENT };
  ShaderProgram(int32_t handle);
  ~ShaderProgram();

  int32_t addVertShader(const std::string& src);
  int32_t addFragShader(const std::string& src);
  int32_t addShader(const std::string& src, ShaderType type);

  int32_t loadVertFromFile(const std::string& filePath);
  int32_t loadFragFromFile(const std::string& filePath);

  void uniform(const std::string& name, Mat4& m);
  void uniform(const std::string& name, float f);

  void linkProgram();

  void useProgram();

  int32_t getProgramHandle() { return programHandle; }

  static std::optional<ShaderProgram> createProgram();

 private:
  int32_t programHandle;
};