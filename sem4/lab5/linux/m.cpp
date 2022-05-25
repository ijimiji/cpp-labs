#include "pipe.hpp"
#include <cmath>
#include <stdint.h>

int main() {
    Pipe("main2m", "m2a", "M", [](vector<int32_t> in) {
        string out;
        for (auto number : in) {
            out += to_string(pow(number, 7));
            out += " ";
        }
        return out;
    });
    return 0;
}