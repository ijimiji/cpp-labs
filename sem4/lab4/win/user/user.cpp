#include "kill.hpp"

auto main()->int32_t{
    SetEnvironmentVariableW(L"PROC_TO_KILL", L"explorer.exe");
    if (getPid("chromium.exe")){
        killProcess("chromium.exe");
    }
    auto pid = getPid("paint.exe");
    if (pid > 0){
        killProcess(pid);
    }
    return 0;
}