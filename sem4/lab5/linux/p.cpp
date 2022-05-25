#include "pipe.hpp"
#include <cmath>

fn main()->int32_t {
    Pipe("a2p", "p2s", "P", [](vector<int32_t> in){
        vector<int32_t> out;
        for (auto number : in){
            out.push_back(pow(number, 3));
        }
        return out;
    });
    return 0;
}