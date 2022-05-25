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
    string apply(string data, function<vector<int32_t>(vector<int32_t>)> f){
        stringstream ss(data);
        int32_t temp;
        string msg;
        vector<int32_t> xs;
        while (ss >> temp){
            xs.push_back(temp);
            // cout << red(std::to_string(temp)) << "\n";
        }
        xs = f(xs);
        for (let &x : xs){
            msg += std::to_string(x);
        }
        return msg;
    }
    public:
    Pipe(string input, string output, string name, function<vector<int32_t>(vector<int32_t>)> f){
        cout << green("Creating pipe " + name) << "\n";

        mkfifo(input.c_str(), rw);

        char buffer[bufferSize];

        let inputHandle = open(input.c_str(), O_RDONLY);
        var bytesRead = 0;
        string data;
        while ((bytesRead = read(inputHandle, buffer, sizeof(buffer))) > 0){
            data += string(buffer);
        }
        close(inputHandle);

        var msg = apply(data, f);
        if (output == "stdout"){
            cout << msg << "\n";
        } else {
            let outputHandle = open(output.c_str(), O_WRONLY);
            write(outputHandle, msg.c_str(), msg.size() + 1);
            close(outputHandle);
        }

        cout << green("Pipe " + name + " done") << "\n";
    }
};