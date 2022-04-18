#include "kill.hpp"
#include <stdint.h>

bool almostEqual(std::string s1, std::string s2) {
    bool equal = true;
    auto it1 = s1.begin();
    auto it2 = s2.begin();
    while (it1 != s1.end() and it2 != s2.end()) {
        if (*it1 == ' ' or *it1 == '\n') {
            it1++;
            continue;
        }
        if (*it2 == ' ' or *it2 == '\n') {
            it2++;
            continue;
        }
        if (*it1 != *it2) {
            equal = false;
            break;
        }
        it1++;
        it2++;
    }
    return equal;
}

std::string getvar(std::string variable){
    DWORD bufferSize = 65535;
    std::string buff;
    buff.resize(bufferSize);
    bufferSize = GetEnvironmentVariableA(variable.c_str(), &buff[0], bufferSize);
    return buff;
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
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL bInheritHandle = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, id);
    if (hProcess == NULL)
        return FALSE;

    auto result = TerminateProcess(hProcess, NULL);

    CloseHandle(hProcess);

    if (result) {
        std::cout << green("Killed process: " + std::to_string(id)) << "\n";
    } else {
        std::cout << red("Could not kill process: " + std::to_string(id))
                  << "\n";
    }
    return result;
}
int32_t getPid(std::string processName){
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return (FALSE);
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return (FALSE);
    }

    do {
        std::string str(pe32.szExeFile);
        str.erase(remove(str.begin(), str.end(), ' '), str.end());

        if (almostEqual(str, processName)) {
            CloseHandle(hProcessSnap);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    return -1;
}

bool killProcess(std::string processName) {
    auto pid = getPid(processName);
    if (pid > 0){
        return killProcess(pid);
    } else {
        return false;
    }
}

