#include "kill.hpp"
#include <cstdlib>

std::string getvar(std::string variable){
    auto var = std::getenv(variable.c_str());
    if (var){
        return std::string(var);
    } else {
        return "";
    }
}

bool killProcessFromVariable(std::string variable) {
    auto var = getvar(variable);
    if (var != "") {
        auto processes = std::string(var);
        std::stringstream ss(processes);
        std::string processName;
        while (std::getline(ss, processName, ',')) {
            killProcess(processName);
        }
        return true;
    } else {
        std::cout << yellow("[LOG] PROC_TO_KILL is empty. Doing nothing...\n");
        return false;
    }
}

std::string red(std::string text) { return "\033[31m" + text + "\033[39m"; }
std::string green(std::string text) { return "\033[32m" + text + "\033[39m"; }
std::string yellow(std::string text) { return "\033[33m" + text + "\033[39m"; }

std::map<std::string, std::string> parseArgs(int32_t argc, char *argv[]) {
    std::map<std::string, std::string> parsedArgs;
    std::vector<std::string> args(argv + 1, argv + argc);
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

bool killProcess(int32_t id) {
    auto success = kill(id, SIGKILL) == 0 ? true : false;

    if (success) {
        std::cout << green("Killed process: " + std::to_string(id)) << "\n";
    } else {
        std::cout << red("Could not kill process: " + std::to_string(id))
                  << "\n";
    }
    return success;
}

void killProcess(std::string processName) {
    char buf[512];
    FILE *cmd_pipe = popen(("pidof " + processName).c_str(), "r");
    fgets(buf, 512, cmd_pipe);
    pclose(cmd_pipe);
    std::string ids(buf);
    std::stringstream ss(ids);
    std::string id;
    while (ss >> id) {
        std::cout << id << "\n";
        killProcess(std::stoi(id));
    }
}
