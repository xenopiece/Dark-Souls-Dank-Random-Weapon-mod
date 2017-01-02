#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <string.h>
#include <time.h>
#include <cstdint>
#include "Random Weapon.h"
#include "GetBaseAdress.h"
#include "GetProcessID.h"
using namespace std;


int main()
{
	GetModuleBase c;
	ProcID P;
	//	RandomWeapon w;
	DWORD Base = 0x47043A8;
	//	DWORD IBase = 0x47467A8; used for icon
	__int64 RWeapon = 0;
	DWORD ProcessID;
	DWORD offset1 = 0x10;
	DWORD offset2 = 0x330;
	//	__int64 fuck = 0;
	int Weapon;
	int Timer;
	wchar_t* WindowName = L"Dark Souls III";
	wchar_t* GameTittle = L"DarkSoulsIII.exe";
	HWND WindowHandle = FindWindow(NULL, WindowName);
	__int64 BaseAdress = c.GetModuleBaseAddress(GameTittle, GameTittle);
	if (BaseAdress == NULL)
	{
		cout << "i have failed baseadr ";
		system("pause");
	}
	else
	{
		ProcessID = P.FindProcessId(L"DarkSoulsIII.exe");
		HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);
		if (ProcessID == NULL)
		{
			cout << "I have failed";
			system("pause");
		}
		else
		{

			cout << "Welcome to the Dark Souls III RandomWeapon Mod by Some idiot online" << endl;
			SetConsoleTitle(L"DarkSoulsIII Random Weapon");
			for (;;) {
				cout << "How fast would you like the mod to switch weapons? max 7 seconds (0 makes it unable to load): ";
				cin >> Timer;
				if (!cin && Timer > 7 && Timer > 0) {
					cout << "error, you're hay,. retry" << endl;
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

			while (true)
			{
				if (chk1 && chk2) {
					srand(clock());

					Weapon = RandomWeapon::Weaponsfcs();

					WriteProcessMemory(hprocess, (LPVOID*)(RWeapon + offset2), &Weapon, sizeof(Weapon), NULL);
				}
				Sleep(Timer * 1000);
			}
			system("pause");
		}
	}
}