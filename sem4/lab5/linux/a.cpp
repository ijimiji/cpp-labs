#include "pipe.hpp"
#include <string>

fn main()->int32_t {
    Pipe("m2a", "a2p", "A", [](vector<int32_t> in) {
        string out;
        for (auto number : in) {
            out += std::to_string(number + 10);
            out += " ";
        }
        return out;
    });
    return 0;
}