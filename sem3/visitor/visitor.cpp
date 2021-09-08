// Посетитель
// Классы: базовый Фигура, 
// наследники Вектор, 
// Окружность, 
// Квадрат(стороны параллельны осям всегда)
// - параллельный перенос
// - масштабирование
// - отражение относительно Ox / Oy
#include <iostream>
#include <utility>

using std::pair;
enum Axis { Ox = 1, Oy = 2 };
#include <iostream>
#include <string>

class Circle;
class Square;
class Vector;

class ShapeVisitor {
public:
  virtual void visit(Circle &ref) = 0;
  virtual void visit(Square &ref) = 0;
  virtual void visit(Vector &ref) = 0;
  virtual ~ShapeVisitor() = default;
};

class Shape {
public:
  virtual void accept(ShapeVisitor &v) = 0;
  virtual ~Shape() = default;
};

class Circle : public Shape {
public:
  void accept(ShapeVisitor &v) override {
    v.visit(*this);
  }
};

class Square : public Shape {
public:
  void accept(ShapeVisitor &v) override {
    v.visit(*this);
  }
};

class Vector : public Shape {
public:
  void accept(ShapeVisitor &v) override {
    v.visit(*this);
  }
};

class Scaler : public ShapeVisitor {
public:
  std::string value;
  void visit(Circle &ref) override {
    value = "Circle";
  }
  void visit(Square &ref) override {
    value = "Square";
  }
  void visit(Vector &ref) override {
    value = "Vector";
  }
};

int main() {
  return 0;
}