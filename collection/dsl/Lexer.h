#pragma once

#include <string>
#include <unordered_map>
#include <vector>

struct LexResult {
  std::string str;
  int32_t lineNum;
  int32_t linePos;
};

class Lexer {
 public:
  enum class Tokens {

  };

  std::vector<LexResult> lex(const std::string& s);

  void consumeWhitespace();

  bool isWhitespace(char c);

  bool isSpecial(char c);

  inline static const std::vector<char> specials = {'(', '[', '{',
                                                    '}', ']', ')'};

  inline static const std::vector<std::string> closing = {")", "]", "}"};
  inline static const std::vector<std::string> opening = {"(", "[", "{"};
};
