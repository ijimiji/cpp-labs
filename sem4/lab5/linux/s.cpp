#include "pipe.hpp"

fn main()->int32_t {
    Pipe("p2s", "s2main", "S", [](vector<int32_t> in) {
        vector<int32_t> out;
        int32_t sum = 0;
        for (auto number : in) {
            sum += number;
        }
        out.push_back(sum);
        return out;
    });
    return 0;
}
