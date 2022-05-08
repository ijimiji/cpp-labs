#include "pipe.hpp"
#include <cmath>
#include <stdint.h>

int main(){
    Pipe(L"main2m", L"m2a", L"M", [](vector<int32_t> in){
        vector<int32_t> out;
        for (auto number : in){
            out.push_back(pow(number, 7));
        }
        return out;
    });
    return 0;
}