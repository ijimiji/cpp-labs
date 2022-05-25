#include "pipe.hpp"
#include <cmath>
#include <stdint.h>

int main() {
    Pipe("main2m", "m2a", "M", [](vector<int32_t> in) {
        vector<int32_t> out;
        for (auto number : in) {
            out.push_back(pow(number, 7));
        }
        return out;
    });
    return 0;
}