#include "pipe.hpp"

fn main()->int32_t {
    Pipe("m2a", "a2p", "A", [](vector<int32_t> in) {
        vector<int32_t> out;
        for (auto number : in) {
            out.push_back(number + 10);
        }
        return out;
    });
    return 0;
}