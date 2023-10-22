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
    const char* dllPath = "C:\\Users\\mason\\OneDrive\\Desktop\\Dev\\Assault Cube Internal Trainer\\Debug\\Assault Cube Internal Trainer.dll";
    const char* processName = "ac_client.exe";
    DWORD processID = 0;

    while (!processID)
    {
        processID = GetProcessID(processName);
        Sleep(30);
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processID);

    if (hProcess && hProcess != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProcess, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (loc)
        {

            WriteProcessMemory(hProcess, loc, dllPath, strlen(dllPath) + 1, 0);
        }

        HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread)
        {
            CloseHandle(hThread);
        }
    }

    if (hProcess)
    {
        CloseHandle(hProcess);
    }

    return 0;
}

