#pragma once
#include <Number.hpp>
#include <math.h>
#include <string>

namespace Math {
class Vector {
  private:
    Number x, y;

  public:
    Vector(Number x, Number y);
    Vector add(Vector other);

    std::string toString();
    double getPolarAngle();
    double getPolarRadius();

    static Vector ZERO_VECTOR;
    static Vector ONE_VECTOR;
};
} // namespace Math