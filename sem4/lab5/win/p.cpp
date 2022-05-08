#include "pipe.hpp"
#include <cmath>
#include <stdint.h>

int main(){
    Pipe(L"a2p", L"p2s", L"P", [](vector<int32_t> in){
        vector<int32_t> out;
        for (auto number : in){
            out.push_back(pow(number, 3));
        }
        return out;
    });
    return 0;
}