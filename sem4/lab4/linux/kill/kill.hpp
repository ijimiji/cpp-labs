#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <signal.h>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

std::string yellow(std::string text);

std::string green(std::string text);

std::string red(std::string text);

std::string getvar(std::string variable);

std::map<std::string, std::string> parseArgs(int32_t argc, char *argv[]);

bool killProcess(int32_t id);

void killProcess(std::string processName);

bool killProcessFromVariable(std::string variable);