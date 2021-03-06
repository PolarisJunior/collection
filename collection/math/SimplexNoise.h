#pragma once
#include "math/Mathf.h"
#include "math/Vector3.h"

// Adapted from http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java

/*
 * A speed-improved simplex noise algorithm for 2D, 3D and 4D in Java.
 *
 * Based on example code by Stefan Gustavson (stegu@itn.liu.se).
 * Optimisations by Peter Eastman (peastman@drizzle.stanford.edu).
 * Better rank ordering method for 4D by Stefan Gustavson in 2012.
 *
 * This could be speeded up even further, but it's useful as it is.
 *
 * Version 2012-03-09
 *
 * This code was placed in the public domain by its original author,
 * Stefan Gustavson. You may use it as you see fit, but
 * attribution is appreciated.
 *
 */

// good step size is about .05
class SimplexNoise {
 public:
  // return a number [-1, 1],
  static double noise(double xin, double yin);
  // return a number [-1, 1]
  static double noise(double xin, double yin, double zin);

 private:
  inline static Vec3i grad3[] = {
      Vec3i(1, 1, 0), Vec3i(-1, 1, 0), Vec3i(1, -1, 0), Vec3i(-1, -1, 0),
      Vec3i(1, 0, 1), Vec3i(-1, 0, 1), Vec3i(1, 0, -1), Vec3i(-1, 0, -1),
      Vec3i(0, 1, 1), Vec3i(0, -1, 1), Vec3i(0, 1, -1), Vec3i(0, -1, -1)};

  inline static short p[] = {
      151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,
      225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190,
      6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117,
      35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136,
      171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158,
      231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,
      245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209,
      76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,
      164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,
      202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,
      58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,
      154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253,
      19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
      228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,
      145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184,
      84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,
      222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156,
      180};

  inline static short perm[512] = {};
  inline static short permMod12[512] = {};

  inline static double F2 = 0.5 * (Mathf::sqrt(3.0) - 1.0);
  inline static double G2 = (3.0 - Mathf::sqrt(3.0)) / 6.0;
  inline static double F3 = 1.0 / 3.0;
  inline static double G3 = 1.0 / 6.0;
  inline static double F4 = (Mathf::sqrt(5.0) - 1.0) / 4.0;
  inline static double G4 = (5.0 - Mathf::sqrt(5.0)) / 20.0;

  static int fastfloor(double x) {
    int xi = (int)x;
    return x < xi ? xi - 1 : xi;
  }

  static double dot(Vec3i g, double x, double y) { return g.x * x + g.y * y; }

  static double dot(Vec3i g, double x, double y, double z) {
    return g.x * x + g.y * y + g.z * z;
  }

  SimplexNoise();

  static SimplexNoise initializer;

  struct Grad {
    double x;
    double y;
    double z;
    double w;

    Grad(double x, double y, double z) : x(x), y(y), z(z) {}
    Grad(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
  };
};
