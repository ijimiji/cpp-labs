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

pid_t procFind(const char* name) 
{
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];

    if (!(dir = opendir("/proc"))) {
        perror("can't open /proc");
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        long lpid = strtol(ent->d_name, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }

        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
        FILE* fp = fopen(buf, "r");

        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
                char* first = strtok(buf, " ");
                if (!strcmp(first, name)) {
                    fclose(fp);
                    closedir(dir);
                    return (pid_t)lpid;
                }
            }
            fclose(fp);
        }

    }

    closedir(dir);
    return -1;
}

auto main()->int32_t{
    setenv("PROC_TO_KILL", "nvim", 1);
    auto success = killProcessFromVariable(std::string("PROC_TO_KILL"));
    if (!success){
        std::cout << red("PROCESS FROM PROC_TO_KILL COULD NOT BE KILLED") << "\n";
    }

    if (procFind("nvim") > 0){
        std::cout << yellow("Killing Neovim") << "\n";
        killProcess("nvim");
        if (procFind("nvim") > 0) {
            std::cout << red("Could not kill Neovim\n");
        } else {
            std::cout << green("Successfully killed Neovim\n");
        }
    }
    auto pid = procFind("alacritty");
    if (pid > 0){
        std::cout << yellow("Killing Alacritty") << "\n";
        killProcess(pid);
        if (procFind("alacritty") > 0) {
            std::cout << red("Could not kill Alacritty\n");
        } else {
            std::cout << green("Successfully killed Alacritty\n");
        }
    }

    return 0;
}