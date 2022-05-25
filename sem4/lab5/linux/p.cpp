#include "pipe.hpp"
#include <cmath>

fn main()->int32_t {
    Pipe("a2p", "p2s", "P", [](vector<int32_t> in){
        string out;
        for (auto number : in){
            out += to_string(pow(number, 3));
        }
        return out;
    });
    return 0;
}