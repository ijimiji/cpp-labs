#pragma once
#include <string>

namespace Math {
class Number {
  private:
    double value;

  public:
    Number(double value);
    Number operator+(Number other);
    Number operator/(Number other);
    Number operator-(Number other);
    Number operator*(Number other);
    double getValue();
    std::string toString();
    static Number ZERO;
    static Number ONE;
};
} // namespace Math