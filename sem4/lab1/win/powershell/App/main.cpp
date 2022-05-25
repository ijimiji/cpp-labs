#include <Number.hpp>
#include <Vector.hpp>
#include <iostream>

using namespace Math;
int main(){
    auto a = Vector(Number(1), Number(3.5));
    auto b = Vector(Number(0), Number(0.5));

    std::cout << a.add(b).toString() << std::endl;
    return 0;
}