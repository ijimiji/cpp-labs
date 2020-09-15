#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    double x;
    std::cout << "Enter x ";
    std::cin >> x;
    int k;
    std::cout << "Enter k ";
    std::cin >> k;

    double accuracy = pow(10, -k);
    double a_n = 1, ch = 1;
    int i = 2;
    while (abs(a_n *= (x * x / i / (i - 1.0))) > accuracy) {
        ch += a_n;
        i += 2;
    }

    double e = std::exp(1.0);
    double ch_1 = (pow(e, x) + pow(e, -x))/2;

    std::cout << std::fixed;
    std::cout << std::setprecision(k);
    std::cout << "The result is " << ch << std::endl;
    std::cout << "The result from e is " << ch_1 << std::endl;
    std::cout << "Result form std is " << cosh(x) << std::endl;
    return 0;
}
