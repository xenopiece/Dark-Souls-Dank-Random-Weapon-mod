/*
Who really looks at the source code, nepSmug

TODO:
Find baseA correctly (so we dont have to update every time)
Also fix icon if mr. nice shoes will ever help us
*/

#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <string.h>
#include <time.h>
#include <cstdint>
#include "Utilities.h"

#define REVISION 39

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

int main()
{
	// Init
	std::string title = "DarkSoulsIII Random Weapon (revision:" + std::to_string(REVISION) + ")";
	SetConsoleTitle(convertCharArrayToLPCWSTR(title.c_str()));
	std::cout << "Welcome to the Dark Souls III RandomWeapon Mod by Some idiot online" << std::endl << std::endl;

	// Offsets
	DWORD BaseA = 0x47043A8;
	__int64 RWeapon = 0;
	DWORD primaryrightweb_offset1 = 0x10;
	DWORD primaryrightweb_offset2 = 0x330;

	// Variables
	int Weapon;
	int Timer;

	HWND WindowHandle = FindWindow(NULL, L"Dark Souls III");
	__int64 BaseAdress = Utils::GetModuleBaseAddress(L"DarkSoulsIII.exe", L"DarkSoulsIII.exe");
	if (BaseAdress == NULL)
	{
		std::cout << "Failed to get baseaddress, is Dark Souls 3 running?" << std::endl;
		goto end;
	}
	else
	{
		DWORD ProcessID = Utils::FindProcessId(L"DarkSoulsIII.exe");
		HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);
		if (ProcessID == NULL)
		{
			std::cout << "Failed to open process, are you running this as admin?" << std::endl;
			goto end;
		}
		else
		{

			for (;;) {
				std::cout << "How fast would you like the mod to switch weapons (seconds)?" << std::endl;
				std::cout << "(under 0 makes the code only execute once, 0 makes the game unloadable, " << std::endl;
				std::cout << "its recommended under 10 for fun): ";
				std::cin >> Timer;
				if (!std::cin) {
					std::cout << "error, your hay, retry" << std::endl;
					continue;
				}
				else {
					break;
				}
			}

			system("cls");
			std::cout << "Welcome to the Dark Souls III RandomWeapon Mod by BobRoss" << std::endl << "Timer set to: " << Timer << std::endl;

			// No error plz dark souls, we luv u <3
			ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + BaseA), &RWeapon, sizeof(RWeapon), NULL);
			ReadProcessMemory(hprocess, (LPVOID*)(RWeapon + primaryrightweb_offset1), &RWeapon, sizeof(RWeapon), NULL);

			while (true)
			{
				Weapon = Utils::Weaponsfcs();

				WriteProcessMemory(hprocess, (LPVOID*)(RWeapon + primaryrightweb_offset2), &Weapon, sizeof(Weapon), NULL);

				Sleep(Timer * 1000);
			}

			goto end;
		}
	}

end:
	system("pause");
	return 1;
}
