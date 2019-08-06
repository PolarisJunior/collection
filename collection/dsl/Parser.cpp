
#include "Parser.h"
#include <iostream>
#include <unordered_map>
#include "Lexer.h"

void Parser::parse(const std::vector<LexResult>& tokens) {
  for (auto& s : tokens) {
    auto it = std::find(Lexer::opening.begin(), Lexer::opening.end(), s.str);
    if (it != Lexer::opening.end()) {
      lastOpening.push(s.str);
    }

    it = std::find(Lexer::closing.begin(), Lexer::closing.end(), s.str);
    if (it != Lexer::closing.end()) {
      if (lastOpening.empty() ||
          lastOpening.top() !=
              (Lexer::opening[std::distance(Lexer::closing.begin(), it)])) {
        std::cout << "Mismatched " << s.str << " line: " << s.lineNum
                  << " char: " << s.linePos << std::endl;
      }

      if (!lastOpening.empty()) {
        lastOpening.pop();
      }
    }
  }

  if (!lastOpening.empty()) {
    std::cout << "not closed" << std::endl;
  }
}