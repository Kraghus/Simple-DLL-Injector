#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcessID(const char* processName)
{
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);

        if (Process32First(hSnapshot, &processEntry))
        {
            do
            {
                if (!_stricmp(processEntry.szExeFile, processName))
                {
                    processID = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &processEntry));
        }
    }
    CloseHandle(hSnapshot);
    return processID;
}

int main()
{
    std::cout << "Hello World!\n";
}

