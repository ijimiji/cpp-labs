#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <string>

typedef std::string (__cdecl* MYPROC)();

int main(void)
{
    std::string result;
    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibrary(TEXT("../Vector/x64/Debug/Vector.dll"));

    if (hinstLib != NULL)
    {
        ProcAdd = (MYPROC)GetProcAddress(hinstLib, "doStuff");

        if (NULL != ProcAdd)
        {
            fRunTimeLinkSuccess = TRUE;
            result = (ProcAdd)();
        }
        fFreeResult = FreeLibrary(hinstLib);
    }

    if (fRunTimeLinkSuccess)
    {
        std::cout << "The vector (1, 2) + (1, 2) is " << result << "\n";
    }
    return 0;
}