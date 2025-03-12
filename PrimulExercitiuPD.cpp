#include <windows.h>
#include <windows.h>
#include <iostream>
#include <tchar.h>

using namespace std;

void afisareVariabileImagePath()
{
    HKEY hKey = 0;
    TCHAR pathOfsubKey[100] = TEXT("SYSTEM\\CurrentControlSet\\Services");

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, pathOfsubKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        cerr << "Eroare la deschidere!" << endl;
    }

    TCHAR name_service[256]; 
    DWORD serviceNumber = 0;
    DWORD nameSize = 0;

    while (true)
    {
        nameSize = sizeof(name_service) / sizeof(TCHAR);

        LONG enumeratedKeys = RegEnumKeyEx(hKey, serviceNumber, name_service, &nameSize, NULL, NULL, NULL, NULL);

        if (enumeratedKeys != ERROR_SUCCESS)
            break;
        
        TCHAR servicePath[1024] = TEXT("");
        wcscpy_s(servicePath, pathOfsubKey);
        wcscat_s(servicePath, TEXT("\\"));
        wcscat_s(servicePath, name_service);

        HKEY hKey_service = NULL;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, servicePath, 0, KEY_READ, &hKey_service) == ERROR_SUCCESS)
        {
            TCHAR imagePath[512]; 
            DWORD pathSize = sizeof(imagePath);
            DWORD type;

            if (RegQueryValueEx(hKey_service, L"ImagePath", NULL, &type, (LPBYTE)imagePath, &pathSize) == ERROR_SUCCESS)
            {
                wcout << "Serviciul: " << name_service << "\n";
                wcout << "ImagePath: " << imagePath << "\n\n";
            }

            RegCloseKey(hKey_service);
        }

        serviceNumber++;
    }

    RegCloseKey(hKey);
}

int main()
{
    afisareVariabileImagePath();
    return 0;
}