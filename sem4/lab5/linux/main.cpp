#include "pipe.hpp"
using std::cin;

fn main()->int32_t{
    string temp;
    string in;
    while (cin >> temp) {
        in += temp;
    }

    char buffer[bufferSize];
    mkfifo("main2m", rw);
    let output = open("main2m", O_WRONLY);
    write(output, in.c_str(), in.size() + 1);
    close(output);
    while (1){
        let input = open("s2main", O_RDONLY);
        read(input, buffer, bufferSize);
        close(input);

        string out (buffer);
        if (out != ""){
            cout << out << "\n";
        }
    }

    return 0;
}