#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <signal.h>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

bool almostEqual(std::string s1, std::string s2);

int32_t getPid(std::string processName);

std::string yellow(std::string text);

std::string green(std::string text);

std::string red(std::string text);

std::string getvar(std::string variable);

std::map<std::string, std::string> parseArgs(int32_t argc, char *argv[]);

bool killProcess(int32_t id);

bool killProcess(std::string processName);

bool killProcessFromVariable(std::string variable);