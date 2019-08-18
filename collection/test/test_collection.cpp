
#include "test_collection.h"
#include <cassert>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "io/File.h"

#include "dsl/Lexer.h"
#include "dsl/LispReader.h"
#include "dsl/Parser.h"

#include "datastructures/LinkedList.h"
#include "misc/MergeSort.h"
#include "misc/QuickSort.h"

#include "network/ClientSocket.h"
#include "network/ServerSocket.h"
#include "network/Socket.h"

#include "game/ecs/GameObject.h"
#include "physics/RigidBody.h"

#include <sstream>

namespace test {
void testComponentCopying() {
  GameObject go = GameObject();
  RigidBody& rbd = go.addComponent<RigidBody>();
  rbd.gravityScale = 6.0;

  assert(&rbd.gameObject() != nullptr);
  RigidBody clone = rbd.copy();

  assert(rbd.gravityScale == clone.gravityScale);
  assert(&clone.gameObject() == nullptr);
  assert(&clone.gameObject() != &rbd.gameObject());
  assert(&go.getComponent<RigidBody>() == &rbd);
}

void runBasicTests() {
  testComponentCopying();
  std::cout << "running basic tests" << std::endl;
  LinkedList<int32_t> ll(0);
  ll.push_back(5);
  ll.push_back(7);
  assert(ll.size() == 3);

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

  Lexer lexer;
  std::string src = File("../res/lisp/lisp.rkt").readAsString();
  auto result = lexer.lex(src);
  for (auto s : result) {
    std::cout << s.str << std::endl;
  }

  Parser parser;
  try {
    parser.parse(result);
  } catch (std::string s) {
    std::cout << s << std::endl;
  }

  LispReader reader;

  // std::istringstream stream(File("../res/lisp/lisp.rkt").readAsString());
  // stream >> std::noskipws;
  // while (!stream.eof()) {
  //   char c;
  //   stream >> c;
  //   std::cout << c;
  // }
  // std::cout << std::endl;

  // ServerSocket socket = ServerSocket(27015);
  // std::unique_ptr<Socket> client = socket.acceptConnection();
  // ClientSocket client = ClientSocket();
  // client.sendMsg("weewHello there");
  // std::cout << client.receive() << std::endl;
}
}  // namespace test