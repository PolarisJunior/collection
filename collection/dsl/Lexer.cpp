

#include "Lexer.h"
#include <cctype>
#include <iostream>

enum class LexerState { CONSUMING_WHITESPACE, MAKING_TOKEN };

bool Lexer::isWhitespace(char c) {
  return std::isspace || c == ',';
}

bool Lexer::isSpecial(char c) {
  return std::find(specials.begin(), specials.end(), c) != specials.end();
}

std::vector<LexResult> Lexer::lex(const std::string& s) {
  LexerState state = LexerState::CONSUMING_WHITESPACE;
  int32_t lineNum = 0;
  int32_t linePos = 0;

  std::vector<LexResult> tokens;
  std::string currentToken = "";

  auto it = s.begin();
  while (it != s.end()) {
    char c = *it;
    switch (state) {
      case LexerState::CONSUMING_WHITESPACE: {
        if (isWhitespace(c)) {
          if (c == '\n') {
            lineNum++;
            linePos = -1;
          }
          ++it;
          ++linePos;
        } else {
          state = LexerState::MAKING_TOKEN;
        }
        break;
      }
      case LexerState::MAKING_TOKEN: {
        if (isWhitespace(c)) {
          tokens.push_back({currentToken, lineNum, linePos});
          currentToken = "";
          state = LexerState::CONSUMING_WHITESPACE;
        } else if (isSpecial(c)) {
          if (!currentToken.empty()) {
            tokens.push_back({currentToken, lineNum, linePos});
            currentToken = "";
          }

          tokens.push_back({std::string(1, c), lineNum, linePos});
          ++it;
          ++linePos;
          state = LexerState::CONSUMING_WHITESPACE;
        } else {
          currentToken.push_back(c);
          ++it;
          ++linePos;
        }
        break;
      }
    }
  }

  if (!currentToken.empty()) {
    tokens.push_back({currentToken, 0, 0});
    currentToken = "";
  }

  return tokens;
}