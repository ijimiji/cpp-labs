#include <iostream>
enum Axis { Ox = 0, Oy = 1 };

class Circle;
class Square;
class Vector;

class Visitor {
  public:
    virtual void visit(Circle &ref) = 0;
    virtual void visit(Square &ref) = 0;
    virtual void visit(Vector &ref) = 0;

    virtual ~Visitor() = default;
};

class Shape {
  public:
    virtual void accept(Visitor &v) = 0;

    virtual ~Shape() = default;
};

class Circle : public Shape {
  public:
    double _radius;
    double _centerX;
    double _centerY;
    Circle(double centerX, double centerY, double radius)
        : _centerX(centerX), _centerY(centerY), _radius(radius) {}

    void accept(Visitor &v) override { v.visit(*this); }
};

class Square : public Shape {
  public:
    double _topLeftX;
    double _topLeftY;
    double _bottomRightX;
    double _bottomRightY;
    Square(double topLeftX, double topLeftY, double bottomRightX,
           double bottomRightY)
        : _topLeftX(topLeftX), _topLeftY(topLeftY), _bottomRightX(bottomRightX),
          _bottomRightY(bottomRightY) {}

    void accept(Visitor &v) override { v.visit(*this); }
};

class Vector : public Shape {
  public:
    double _x;
    double _y;
    Vector(double x, double y) : _x(x), _y(y) {}
    void accept(Visitor &v) override { v.visit(*this); }
};

class Scaler : public Visitor {
  public:
    double _factor;

  public:
    Scaler(double factor) : _factor(factor){};
    void visit(Circle &ref) override { ref._radius = ref._radius * _factor; }
    void visit(Square &ref) override {
        ref._topLeftX = ref._topLeftX * _factor;
        ref._topLeftY = ref._topLeftY * _factor;
    }
    void visit(Vector &ref) override {
        ref._x = ref._x * _factor;
        ref._y = ref._y * _factor;
    }
};

class Mirrorer : public Visitor {
  public:
    Axis _axis;

  public:
    Mirrorer(Axis axis) : _axis(axis){};
    void visit(Circle &ref) override {
        if (_axis == Ox) {
            ref._centerY = -ref._centerY;
        } else {
            ref._centerY = -ref._centerY;
        }
    }
    void visit(Square &ref) override {
        if (_axis == Ox) {
            ref._topLeftY = -ref._topLeftY;
            ref._bottomRightY = -ref._bottomRightY;
        } else {
            ref._topLeftX = -ref._topLeftX;
            ref._bottomRightX = -ref._bottomRightX;
        }
    }
    void visit(Vector &ref) override {
        if (_axis == Ox) {
            ref._y = -ref._y;
        } else {
            ref._x = -ref._x;
        }
    }
};

class Mover : public Visitor {
  public:
    double _dx;
    double _dy;

  public:
    Mover(double dx, double dy) : _dx(dx), _dy(dy){};
    void visit(Circle &ref) override {
        ref._centerX = ref._centerX + _dx;
        ref._centerY = ref._centerY + _dy;
    }
    void visit(Square &ref) override {
        ref._bottomRightX = ref._bottomRightX + _dx;
        ref._bottomRightY = ref._bottomRightY + _dy;
        ref._topLeftX = ref._topLeftX + _dx;
        ref._topLeftY = ref._topLeftY + _dy;
    }
    void visit(Vector &ref) override {
        ref._x = ref._x + _dx;
        ref._y = ref._y + _dy;
    }
};
int main() {
    Circle foo(1, 2, 10);
    Square bar(1, 1, 2, 0);
    Vector baz(1, 1);
    Shape *elements[] = {&foo, &bar, &baz};

    for (auto elem : elements) {
        Scaler doubler(2);
        elem->accept(doubler);
    }
    std::cout << foo._radius << std::endl;
    return 0;
}