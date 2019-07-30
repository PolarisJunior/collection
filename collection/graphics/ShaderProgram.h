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

  void uniform(const std::string& name, const Mat4& m);
  // warning: be careful of ambiguity between floats and integers
  void uniform(const std::string& name, float f);
  // Note use this to load uniform variables as sampler types
  void uniform(const std::string& name, int32_t v);

  // Links the program after adding vertex and fragment shaders
  void linkProgram();

  // Set GL to use this shader program for subsequent rendering
  // links the program if not already linked
  void useProgram();

  // Returns the programHandle used by openGL
  int32_t getProgramHandle() { return programHandle; }

  static std::optional<ShaderProgram> createProgram();

 private:
  int32_t programHandle;
  bool wasLinked = false;
};