#include "kill.hpp"
#include <cstdlib>
#include <processenv.h>

auto main(int32_t argc, char *argv[]) -> int32_t {
    SetEnvironmentVariableW(L"PROC_TO_KILL", L"explorer.exe");
    killProcess("explorer.exe");
    auto args = parseArgs(argc, argv);
    killProcessFromVariable("PROC_TO_KILL");
    if (args.find("id") != args.end()) {
        killProcess(std::stoi(args["id"]));
    } else if (args.find("name") != args.end()) {
        killProcess(args["name"]);
    }
    return 0;
}