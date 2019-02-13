
#include <assert.h>
#include <iostream>
#include <string>
#include "../math/Vector2.h"

int test(int argc, char** argv) {
  Vector2 vec1(1.0f, 1.0f);
  Vector2 vec2(2.0f, 2.0f);

  assert((vec1 * 2).equals(vec2));
  assert((vec1 + vec1).equals(vec2));
  assert(vec1 == vec1);
  assert(fabs(vec1.normalized().length() - 1) < 0.00001);

  vec1 *= 2.0;
  assert(vec1.equals(vec2));
  vec2 -= Vector2::right() + Vector2::down();
  assert(vec2.equals(Vector2::right() + Vector2::down()));
  std::cout << "done" << std::endl;

    return EXIT_SUCCESS;
}