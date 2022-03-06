#include "Vector.hpp"

Math::Vector::Vector(Number x, Number y) : x(x), y(y) {}

Math::Vector Math::Vector::add(Vector other) {
    return Vector(this->x + other.x, this->y + other.y);
}

std::string Math::Vector::toString() {
    return "(" + x.toString() + ", " + y.toString() + ")";
}

double Math::Vector::getPolarAngle() { return atan((x / y).getValue()); }

double Math::Vector::getPolarRadius() {
    return sqrt((x * x + y * y).getValue());
}

Math::Vector Math::Vector::ONE_VECTOR =
    Math::Vector(Math::Number::ONE, Math::Number::ONE);
Math::Vector Math::Vector::ZERO_VECTOR =
    Math::Vector(Math::Number::ZERO, Math::Number::ZERO);