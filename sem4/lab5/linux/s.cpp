#include "pipe.hpp"
#include <string>

fn main()->int32_t {
    Pipe("p2s", "stdout", "S", [](vector<int32_t> in) {
        int32_t sum = 0;
        for (auto number : in) {
            sum += number;
        }
        return std::to_string(sum);
    });
    return 0;
}
