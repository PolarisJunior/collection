
#include "test_collection.h"
#include <cassert>
#include <cctype>
#include <iostream>
#include <vector>
#include "datastructures/LinkedList.h"
#include "dsl/Lexer.h"
#include "dsl/Parser.h"
#include "io/File.h"
#include "misc/MergeSort.h"
#include "misc/QuickSort.h"

namespace test {
void runBasicTests() {
  // LinkedList<int32_t> ll(0);
  // ll.push_back(5);
  // ll.push_back(7);
  // assert(ll.size() == 3);
  // std::cout << "Tests Passed" << std::endl;

  // std::vector<int32_t> vec{0, 1, 5, -1, -3, 8, 9, 10, -5, -6};
  // QuickSort::sort<int32_t>(vec);
  // for (int32_t e : vec) {
  //   std::cout << e << ", ";
  // }
  // std::cout << "\n";

  // std::vector<int32_t> res;
  // res = MergeSort::sort<int32_t>(vec);
  // for (int32_t e : res) {
  //   std::cout << e << ", ";
  // }
  // std::cout << "\n";

  std::cout << std::isspace('\n') << " " << std::isspace('\r') << std::endl;
  Lexer lexer;
  std::string src = File("../res/lisp/lisp.rkt").readAsString();
  auto result = lexer.lex(src);
  for (auto s : result) {
    std::cout << s.str << std::endl;
  }

  Parser parser;
  parser.parse(result);
}
}  // namespace test