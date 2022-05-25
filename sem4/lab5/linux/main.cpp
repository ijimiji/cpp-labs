#include "pipe.hpp"
using std::cin;

fn main()->int32_t{
    string temp;
    string in = "1 2 3 5 5243 6 6453";

    // while (cin >> temp) {
    //     in += temp;
    // }

    char buffer[bufferSize];
    mkfifo("main2m", rw);
    let output = open("main2m", O_WRONLY);
    write(output, in.c_str(), in.size());
    close(output);

    return 0;
}