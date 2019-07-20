#pragma once

#include <cstdint>
#include <optional>
#include <string>

class ShaderProgram {
 public:
  enum class ShaderType { VERTEX, FRAGMENT };
  ShaderProgram(int32_t handle);
  ~ShaderProgram();

  int32_t addVertShader(const std::string& src);
  int32_t addFragShader(const std::string& src);
  int32_t addShader(const std::string& src, ShaderType type);

  void finalizeProgram();

  void useProgram();

  int32_t getProgramHandle() { return programHandle; }

  static std::optional<ShaderProgram> createProgram();

 private:
  int32_t programHandle;
};