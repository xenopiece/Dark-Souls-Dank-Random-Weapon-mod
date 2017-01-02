#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <string.h>
#include <time.h>
#include <cstdint>
#include "Utilities.h"

int main()
{
	// Init
	SetConsoleTitle(L"DarkSoulsIII Random Weapon");
	std::cout << "Welcome to the Dark Souls III RandomWeapon Mod by Some idiot online" << std::endl;

	// Offsets
	DWORD Base = 0x47043A8;
	//	DWORD IBase = 0x47467A8; used for icon
	__int64 RWeapon = 0;
	DWORD ProcessID;
	DWORD offset1 = 0x10;
	DWORD offset2 = 0x330;

	// Variables
	int Weapon;
	int Timer;

	HWND WindowHandle = FindWindow(NULL, L"Dark Souls III");
	__int64 BaseAdress = Utils::GetModuleBaseAddress(L"DarkSoulsIII.exe", L"DarkSoulsIII.exe");
	if (BaseAdress == NULL)
	{
		std::cout << "Failed to get baseaddress, is Dark Souls 3 running?" << std::endl;
		// Bad way of ending, LUUL
		system("pause");
		exit(0);
	}
	else
	{
		ProcessID = Utils::FindProcessId(L"DarkSoulsIII.exe");
		HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);
		if (ProcessID == NULL)
		{
			std::cout << "Failed to open process, are you running this as admin?" << std::endl;
			// Bad way of ending, LUUL
			system("pause");
			exit(0);
		}
		else
		{
			for (;;) {
				std::cout << "How fast would you like the mod to switch weapons? max 7 seconds (0 makes it unable to load): ";
				std::cin >> Timer;
				if (!std::cin && Timer > 7 && Timer > 0) {
					std::cout << "error, you're hay, retry" << std::endl;
					continue;
				}
				else {
					break;
				}
			}

			system("cls");
			std::cout << "Welcome to the Dark Souls III RandomWeapon Mod by BobRoss" << std::endl << "Timer set to: " << Timer << std::endl;

			// No error plz dark souls, we luv u <3
			BOOL chk1 = ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + Base), &RWeapon, sizeof(RWeapon), NULL);
			BOOL chk2 = ReadProcessMemory(hprocess, (LPVOID*)(RWeapon + offset1), &RWeapon, sizeof(RWeapon), NULL);

			if (!chk1 || !chk2) {
				std::cout << "Error, failed to read process memory" << std::endl;
				// Bad way of ending, LUUL
				system("pause");
				exit(0);
			}

			while (true)
			{
				Weapon = Utils::Weaponsfcs();

				WriteProcessMemory(hprocess, (LPVOID*)(RWeapon + offset2), &Weapon, sizeof(Weapon), NULL);

				Sleep(Timer * 1000);
			}

			system("pause");
		}
	}
}