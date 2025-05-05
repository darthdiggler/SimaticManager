//Command gcc -shared -o TestProject.dll TestProject.c

// TestProject.c

#include <windows.h>

// This function will be exported from the DLL
__declspec(dllexport) int MultiplyNumbers(int a, int b)
{
    return a * b;
}

// Optional: DLL entry point (not strictly needed unless you want startup/shutdown logic)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}