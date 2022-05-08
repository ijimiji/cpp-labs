#include "pipe.hpp"
#include <cmath>
#include <stdint.h>

int main(){
    Pipe(L"m2a", L"a2p", L"A", [](vector<int32_t> in){
        vector<int32_t> out;
        for (auto number : in){
            out.push_back(number + 10);
        }
        return out;
    });
    return 0;
}