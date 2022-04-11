#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <signal.h>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

using std::cout;
using std::map;
using std::string;
using std::vector;

string yellow(string text) { return "\033[33m" + text + "\033[39m"; }

string green(string text) { return "\033[32m" + text + "\033[39m"; }

string red(string text) { return "\033[31m" + text + "\033[39m"; }

auto parseArgs(int32_t argc, char *argv[]) {
    map<string, string> parsedArgs;
    vector<string> args(argv + 1, argv + argc);
    for (const auto &arg : args) {
        if (arg == "--id") {
            parsedArgs["id"] = *(&arg + 1);
        }
        if (arg == "--name") {
            parsedArgs["name"] = *(&arg + 1);
        }
    }
    return parsedArgs;
}

auto killProcess(int32_t id) {
    auto success = kill(id, SIGKILL) == 0 ? true : false;

    if (success) {
        cout << green("Killed process: " + std::to_string(id)) << "\n";
    } else {
        cout << red("Could not kill process: " + std::to_string(id)) << "\n";
    }
}
auto killProcess(string processName) {
    char buf[512];
    FILE *cmd_pipe = popen(("pidof " + processName).c_str(), "r");
    fgets(buf, 512, cmd_pipe);
    pclose(cmd_pipe);
    string ids(buf);
    std::stringstream ss(ids);
    string id;
    while (ss >> id) {
        killProcess(std::stoi(id));
    }
}

auto main(int32_t argc, char *argv[]) -> int32_t {
    auto args = parseArgs(argc, argv);
    auto var = std::getenv("PROC_TO_KILL");
    if (var) {
        auto processes = string(var);
        std::stringstream ss(processes);
        string processName;
        while (std::getline(ss, processName, ',')) {
            killProcess(processName);
        }
    } else {
        std::cout << yellow("[LOG] PROC_TO_KILL is empty. Doing nothing...\n");
    }

    if (args.find("id") != args.end()) {
        killProcess(std::stoi(args["id"]));
    } else if (args.find("name") != args.end()) {
        killProcess(args["name"]);
    }
    return 0;
}