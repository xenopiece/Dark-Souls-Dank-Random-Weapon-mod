#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <string.h>
#include <time.h>
#include <cstdint>
#include "Utilities.h"

//http://forum.cheatengine.org/viewtopic.php?t=589191&postdays=0&postorder=asc&start=3645
//https://puu.sh/t0WQw/325008ca12.webm
//http://forum.cheatengine.org/viewtopic.php?t=589191&postdays=0&postorder=asc&start=3660
__int64 process_ReadRightWeaponIcon(DWORD currentrite, HANDLE hprocess, __int64 BaseAdress)
{
	__int64 RWeaponIcon = 0;

	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x70), &RWeaponIcon, sizeof(RWeaponIcon), NULL);
	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x68), &RWeaponIcon, sizeof(RWeaponIcon), NULL);
	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x68), &RWeaponIcon, sizeof(RWeaponIcon), NULL);
	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x0), &RWeaponIcon, sizeof(RWeaponIcon), NULL);

	int64_t result = RWeaponIcon - currentrite;
	RWeaponIcon = 0;

	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x70), &RWeaponIcon, sizeof(RWeaponIcon), NULL);
	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x68), &RWeaponIcon, sizeof(RWeaponIcon), NULL);
	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + 0x68), &RWeaponIcon, sizeof(RWeaponIcon), NULL);
	ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + result), &RWeaponIcon, sizeof(RWeaponIcon), NULL);

	return RWeaponIcon;
}



int main()
{
	// Init
	SetConsoleTitle(L"DarkSoulsIII Random Weapon");
	std::cout << "Welcome to the Dark Souls III RandomWeapon Mod by Some idiot online" << std::endl;

	// Offsets
	DWORD BaseA = 0x47043A8;
	//	DWORD IBase = 0x47467A8; used for icon
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
		// Bad way of ending, LUUL
		system("pause");
		exit(0);
	}
	else
	{
		DWORD ProcessID = Utils::FindProcessId(L"DarkSoulsIII.exe");
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
			// Small tests
			// NOPE
//			printf("%.2X\n", process_ReadRightWeaponIcon(0x7FFA2AF429A, hprocess, BaseAdress));

			// NOPE
/*
autoAssemble([[
aobscanmodule(Findit,DarkSoulsIII.exe,48 8B 05 ?? ?? ?? ?? 48 85 C0 ?? ?? 48 8b 40 ?? C3)
registersymbol(Findit)
]])
local addr = getAddress("Findit")
addr = addr + readInteger(addr + 3) + 7
unregisterSymbol("BaseA")
registerSymbol("BaseA", addr, true)
*/
/*
			DWORD_PTR addrGameContext = Utils::FindPatternEx(hprocess, (PBYTE)"\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0\x00\x00\x48\x8b\x40\x00\xC3", "xxx????xxx??xxx?x", BaseAdress, 0x00A000000);
			DWORD_PTR OffsetClientGameContext = 0;
			OffsetClientGameContext = Utils::ResolveRelativePtr(hprocess, addrGameContext, 0);
			// prints 447043A8

			OffsetClientGameContext = OffsetClientGameContext + (static_cast<int>(OffsetClientGameContext) + 3) + 7;
			printf("%.2X\n", OffsetClientGameContext);
			BaseA = OffsetClientGameContext;
*/

//			system("pause");

			for (;;) {
				std::cout << "How fast would you like the mod to switch weapons? (0 makes the game unloadable, its recommended under 10 for fun): ";
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

			system("pause");
		}
	}
}