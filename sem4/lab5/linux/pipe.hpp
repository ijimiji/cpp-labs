#define var auto
#define let const auto
#define fn auto
#define running 1
#define rw 0666
#define bufferSize 128
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <sstream>

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using std::string, std::vector, std::cout, std::function, std::stringstream;

string red(string text) { return "\033[31m" + text + "\033[39m"; }
string green(string text) { return "\033[32m" + text + "\033[39m"; }
string yellow(string text) { return "\033[33m" + text + "\033[39m"; }

class Pipe{
    string apply(char *rawData, function<vector<int32_t>(vector<int32_t>)> f){
        stringstream ss((string(rawData)));
        int32_t temp;
        string msg;
        vector<int32_t> xs;
        while (ss >> temp){
            xs.push_back(temp);
        }
        xs = f(xs);
        for (let &x : xs){
            msg += x;
        }
        return msg;
    }
    public:
    Pipe(string input, string output, string name, function<vector<int32_t>(vector<int32_t>)> f){
        cout << green("Creating pipe " + name) << "\n";

        let inputName = input.c_str();
        let outputName = output.c_str();
        mkfifo(inputName, rw);

        char buffer[bufferSize];
        {
            let input = open(inputName, O_RDONLY);
            read(input, buffer, bufferSize);
            close(input);

            var msg = apply(buffer, f);

            let output = open(outputName, O_WRONLY);
            write(output, msg.c_str(), msg.size() + 1);
            close(output);
        }
        cout << green("Pipe " + name + " done") << "\n";
    }
};