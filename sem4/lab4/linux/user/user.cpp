#include "kill.hpp"
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

auto main(int32_t argc, char *argv[])->int32_t{
    fork();
    execv("./kill", argv);
    return 0;
}