#pragma once

#include <stack>
#include <string>
#include <vector>
#include "Lexer.h"

class Parser {
 public:
  void parse(const std::vector<LexResult>& tokens);

  std::stack<std::string> lastOpening;
};
