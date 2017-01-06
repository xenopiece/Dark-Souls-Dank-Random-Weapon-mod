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

// 80x25
std::vector<std::string> secretascii = {
"                    .~ZZZ$Z$Z7I,.       ",
"                  IZONDDNNNNDN88Z=.     ",
"                ,7ZNN8MNMMNMNMNN8Z?.    ",
"                7O8DMNMMMNMNNMNDDN87.   ",
"               $ZD8DNDD888NNMNMDNNNO.   ",
"               $ODDOOZ8OOODDDDNMNMN8Z.  ",
"               IDDD8OI7Z$7OOD8DNMNND$.. ",
"               ZODND7IZ8=$Z8NMDNDDDNO.  ",
"               $OD8D~7:?=+O$7Z8DNND8$.  ",
"               ~OODD~:=~=+OZ?7ZDNNNO?.  ",
"                7Z8O~~O:~I$ZO$Z8NN$=~   ",
"                 Z$Z~I$787ZDDDDDND~~.   ",
"                  7ZZ$Z=~?7ZDO8D?.      ",
"                    ZOII~7788DM++?..    ",
".                    7+I77$Z7Z???+?.    ",
"?I77...             .,,7D8O7?+++7??+=.  ",
"II777II: .I=.       ::~=??,~~~:Z~~==+?. ",
"$$$I$77ID==M=??.     ::=~:::::,::~~=+++.",
".,ZO?IOIDD=+N+?.     ,,,++:::,::::~=+++.",
"    $$DOO7?=?I:.     ,?=?=,:~,.,,:+~?++.",
"           =+I?$88DDD~~:,,,:,:,+,:=,++?.",
"           ???$77$ZZ.,,,,,,,+,=,,,:=++?.",
"            .??I7+:,,,,,,,,,,~,,,:~+?+?.",
"              .I7I$,:,,,,,:~,:,,,,~+?++.",
"                ?I,,,,,,,~,,,,,:,,~+?++,",
"                 ................,.....",
};

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

			if (Timer == 0) { // How deer u disobey us
				system("cls");
				SetConsoleTitle(L"No mistakes, only happy little accidents");

				HWND console = GetConsoleWindow();
				RECT r;
				GetWindowRect(console, &r); //stores the console's current dimensions
				MoveWindow(console, r.left, r.top, 400, 400, TRUE);

				// This wont actually work, nepSmug
				EnableScrollBar(console, SB_BOTH, ESB_DISABLE_BOTH);

				for (int i = 0; i < secretascii.size(); i++) {
					std::cout << secretascii[i].c_str() << std::endl;
				}
			}

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
