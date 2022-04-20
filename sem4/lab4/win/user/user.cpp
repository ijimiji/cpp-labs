#include "kill.hpp"
#include <processthreadsapi.h>
#include <stdint.h>
#include <string>
#include <winnt.h>

std::wstring Str2Wstr(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

auto main(int32_t argc, char *argv[])->int32_t{
    SetEnvironmentVariableW(L"PROC_TO_KILL", L"chromium.exe");
    std::vector<std::wstring> args;
    for (auto str = argv+1; str != argv+argc; str++){
        args.push_back(Str2Wstr(std::string(*str)));
    }
    for (auto x : args){
        std::wcout << x << "\n";
    }

    STARTUPINFOW process_startup_info{ 0 };
    process_startup_info.cb = sizeof(process_startup_info);
    PROCESS_INFORMATION process_info{0};

    std::wstring cmd = L"\".\\kill.exe\" ";
    for (auto &arg : args){
        cmd.append(arg);
        cmd.append(L" ");
    }

    // connecting strings here
    if (CreateProcessW(NULL, (LPWSTR) cmd.data(), NULL, NULL, TRUE, 0, NULL,
                       NULL, &process_startup_info, &process_info)) {
        WaitForSingleObject(process_info.hProcess, INFINITE);
        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);
    }

    SetEnvironmentVariableW(L"PROC_TO_KILL", NULL);
    return 0;
}