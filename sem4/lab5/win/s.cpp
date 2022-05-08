#include "pipe.hpp"
#include <cmath>
#include <stdint.h>

int main(){
    Pipe(L"p2s", L"stdout", L"S", [](vector<int32_t> in){
        vector<int32_t> out;
        int32_t sum = 0;
        for (auto number : in){
            sum += number; 
        }
        out.push_back(sum);
        return out;
    });
    system("pause");
    return 0;
}