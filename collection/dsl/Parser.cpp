
#include "Parser.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Lexer.h"

void Parser::parse(const std::vector<LexResult>& tokens) {
  for (auto& s : tokens) {
    auto it = std::find(Lexer::opening.begin(), Lexer::opening.end(), s.str);
    if (it != Lexer::opening.end()) {
      lastOpening.push(s.str);
      continue;
    }

    it = std::find(Lexer::closing.begin(), Lexer::closing.end(), s.str);
    if (it != Lexer::closing.end()) {
      if (lastOpening.empty() ||
          lastOpening.top() !=
              (Lexer::opening[std::distance(Lexer::closing.begin(), it)])) {
        std::stringstream ss;
        ss << "Mismatched " << s.str << " line: " << s.lineNum
           << " char: " << s.linePos;
        throw ss.str();
        break;
      }

      if (!lastOpening.empty()) {
        lastOpening.pop();
      }
      continue;
    }
  }

  if (!lastOpening.empty()) {
    throw "Lisp program mismatched closing";
  }
}