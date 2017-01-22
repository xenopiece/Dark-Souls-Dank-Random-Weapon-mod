#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "Utilities.h"
#include "MyForm.h"

#pragma comment(lib, "User32.lib")


using namespace System::Threading;

void printDBG(std::string msg)
{
	std::ofstream myfile;
	myfile.open("debug.txt", std::ios_base::app | std::ios_base::out);
	myfile << msg << "\n";
	myfile.close();
}

void printDBG(int num) { printDBG(std::to_string(num)); }
void printDBG(double num) { printDBG(std::to_string(num)); }

double glbl;
std::vector<std::string> enableweapons;
bool stopthread = false;
void changeweapon()
{
	// Offsets
	DWORD BaseA = 0x47043A8;
	__int64 RWeapon = 0;
	DWORD primaryrightweb_offset1 = 0x10;
	DWORD primaryrightweb_offset2 = 0x330;

	// Variables
	int Weapon;

	HWND WindowHandle = FindWindow(NULL, L"Dark Souls III");
	__int64 BaseAdress = Utils::GetModuleBaseAddress(L"DarkSoulsIII.exe", L"DarkSoulsIII.exe");
	if (BaseAdress == NULL)
	{
//		std::cout << "Failed to get baseaddress, is Dark Souls 3 running?" << std::endl;
		goto error_baseaddress;
	}
	else
	{
		DWORD ProcessID = Utils::FindProcessId(L"DarkSoulsIII.exe");
		HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);
		if (ProcessID == NULL)
		{
//			std::cout << "Failed to open process, are you running this as admin?" << std::endl;
			goto error_processid;
		}
		else
		{
			// No error plz dark souls, we luv u <3
			ReadProcessMemory(hprocess, (LPVOID*)(BaseAdress + BaseA), &RWeapon, sizeof(RWeapon), NULL);
			ReadProcessMemory(hprocess, (LPVOID*)(RWeapon + primaryrightweb_offset1), &RWeapon, sizeof(RWeapon), NULL);

			while (true) {
				if (stopthread == true) {
					stopthread = false;
					goto end;
				}

				Weapon = Utils::Weaponsfcs(enableweapons);

				WriteProcessMemory(hprocess, (LPVOID*)(RWeapon + primaryrightweb_offset2), &Weapon, sizeof(Weapon), NULL);

				Sleep((DWORD)(glbl * 1000));
			}

			goto error;
		}
	}

	// Errors come here, add error handling
error_processid:
	::MessageBox(0, L"Failed to open process, are you running this as admin?", L"DS3 Random Weapon mod", MB_ICONERROR);
	return;
error_baseaddress:
	::MessageBox(0, L"Failed to get baseaddress, is Dark Souls 3 running?", L"DS3 Random Weapon mod", MB_ICONERROR);
	return;
error:
	::MessageBox(0, L"'Something happened' Microsoft 2016", L"DS3 Random Weapon mod", MB_ICONERROR);
	return;
end:
	return;
}

void merge(std::vector<std::string> toinsert, std::vector<std::string> tobeinserted)
{
	for (int i = 0; i < tobeinserted.size(); i++) {
//		toinsert.push_back(tobeinserted[i]);
//		APPARENTLY toinsert FUCKS EVERYTHING UP AND I DONT WANT TO CHANGE EVERYTHING
		enableweapons.push_back(tobeinserted[i]);
	}
}

void somefunction(double timer, std::vector<std::string> stuff)
{
	enableweapons.clear();

	bool standard = false;
	bool bows = false;
	bool whips = false;
	bool shields = false;
	// Infusions
	bool heavy = false;
	bool sharp = false;
	bool refined = false;
	bool simple = false;
	bool crystal = false;
	bool fire = false;
	bool chaos = false;
	bool lightning = false;
	bool deep = false;
	bool dark = false;
	bool poison = false;
	bool blood = false;
	bool raw = false;
	bool blessed = false;
	bool hollow = false;
	// SECRET
	bool secret = false;

	for (int i = 0; i < stuff.size(); i++) {
		std::string current = stuff[i];

		if (current.find("Standard") != std::string::npos) { standard = true; }
		if (current.find("Bows") != std::string::npos) { bows = true; }
		if (current.find("Whips") != std::string::npos) { whips = true; }
		if (current.find("Shields") != std::string::npos) { shields = true; }
		// Infusions
		if (current.find("Heavy") != std::string::npos) { heavy = true; }
		if (current.find("Sharp") != std::string::npos) { sharp = true; }
		if (current.find("Refined") != std::string::npos) { refined = true; }
		if (current.find("Simple") != std::string::npos) { simple = true; }
		if (current.find("Crystal") != std::string::npos) { crystal = true; }
		if (current.find("Fire") != std::string::npos) { fire = true; }
		if (current.find("Chaos") != std::string::npos) { chaos = true; }
		if (current.find("Lightning") != std::string::npos) { lightning = true; }
		if (current.find("Deep") != std::string::npos) { deep = true; }
		if (current.find("Dark") != std::string::npos) { dark = true; }
		if (current.find("Poison") != std::string::npos) { poison = true; }
		if (current.find("Blood") != std::string::npos) { blood = true; }
		if (current.find("Raw") != std::string::npos) { raw = true; }
		if (current.find("Blessed") != std::string::npos) { blessed = true; }
		if (current.find("Hollow") != std::string::npos) { hollow = true; }
		// SECRET
		if (current.find("SECRET") != std::string::npos) { secret = true; }
	}

	if (standard == true) {
		merge(enableweapons, standardweapons);
		if (heavy == true) {
			merge(enableweapons, StandardWeapon_Heavy);
		}
		if (sharp == true) {
			merge(enableweapons, StandardWeapon_Sharp);
		}
		if (refined == true) {
			merge(enableweapons, StandardWeapon_Refined);
		}
		if (simple == true) {
			merge(enableweapons, StandardWeapon_Simple);
		}
		if (crystal == true) {
			merge(enableweapons, StandardWeapon_Crystal);
		}
		if (fire == true) {
			merge(enableweapons, StandardWeapon_Fire);
		}
		if (chaos == true) {
			merge(enableweapons, StandardWeapon_Chaos);
		}
		if (lightning == true) {
			merge(enableweapons, StandardWeapon_Lightning);
		}
		if (deep == true) {
			merge(enableweapons, StandardWeapon_Deep);
		}
		if (dark == true) {
			merge(enableweapons, StandardWeapon_Dark);
		}
		if (poison == true) {
			merge(enableweapons, StandardWeapon_Poison);
		}
		if (blood == true) {
			merge(enableweapons, StandardWeapon_Blood);
		}
		if (raw == true) {
			merge(enableweapons, StandardWeapon_Raw);
		}
		if (blessed == true) {
			merge(enableweapons, StandardWeapon_Blessed);
		}
		if (hollow == true) {
			merge(enableweapons, StandardWeapon_Hollow);
		}
	}
	if (bows == true) {
		merge(enableweapons, StandardBows);
	}
	if (whips == true) {
		merge(enableweapons, StandardWhip);
		if (heavy == true) {
			merge(enableweapons, StandardWhip_Heavy);
		}
		if (sharp == true) {
			merge(enableweapons, StandardWhip_Sharp);
		}
		if (refined == true) {
			merge(enableweapons, StandardWhip_Refined);
		}
		if (simple == true) {
			merge(enableweapons, StandardWhip_Simple);
		}
		if (crystal == true) {
			merge(enableweapons, StandardWhip_Crystal);
		}
		if (fire == true) {
			merge(enableweapons, StandardWhip_Fire);
		}
		if (chaos == true) {
			merge(enableweapons, StandardWhip_Chaos);
		}
		if (lightning == true) {
			merge(enableweapons, StandardWhip_Lightning);
		}
		if (deep == true) {
			merge(enableweapons, StandardWhip_Deep);
		}
		if (dark == true) {
			merge(enableweapons, StandardWhip_Dark);
		}
		if (poison == true) {
			merge(enableweapons, StandardWhip_Poison);
		}
		if (blood == true) {
			merge(enableweapons, StandardWhip_Blood);
		}
		if (raw == true) {
			merge(enableweapons, StandardWhip_Raw);
		}
		if (blessed == true) {
			merge(enableweapons, StandardWhip_Blessed);
		}
		if (hollow == true) {
			merge(enableweapons, StandardWhip_Hollow);
		}
	}
	if (shields == true) {
		merge(enableweapons, StandardShields);
		if (heavy == true) {
			merge(enableweapons, StandardShields_Heavy);
		}
		if (sharp == true) {
			merge(enableweapons, StandardShields_Sharp);
		}
		if (refined == true) {
			merge(enableweapons, StandardShields_Refined);
		}
		if (simple == true) {
			merge(enableweapons, StandardShields_Simple);
		}
		if (crystal == true) {
			merge(enableweapons, StandardShields_Crystal);
		}
		if (fire == true) {
			merge(enableweapons, StandardShields_Fire);
		}
		if (chaos == true) {
			merge(enableweapons, StandardShields_Chaos);
		}
		if (lightning == true) {
			merge(enableweapons, StandardShields_Lightning);
		}
		if (deep == true) {
			merge(enableweapons, StandardShields_Deep);
		}
		if (dark == true) {
			merge(enableweapons, StandardShields_Dark);
		}
		if (poison == true) {
			merge(enableweapons, StandardShields_Poison);
		}
		if (blood == true) {
			merge(enableweapons, StandardShields_Blood);
		}
		if (raw == true) {
			merge(enableweapons, StandardShields_Raw);
		}
		if (blessed == true) {
			merge(enableweapons, StandardShields_Blessed);
		}
		if (hollow == true) {
			merge(enableweapons, StandardShields_Hollow);
		}
	}

	if (secret == true) {
		for (int i = 0; i < 4; i++) {
			merge(enableweapons, StandardShields);
			merge(enableweapons, StandardShields_Heavy);
			merge(enableweapons, StandardShields_Sharp);
			merge(enableweapons, StandardShields_Refined);
			merge(enableweapons, StandardShields_Simple);
			merge(enableweapons, StandardShields_Crystal);
			merge(enableweapons, StandardShields_Fire);
			merge(enableweapons, StandardShields_Chaos);
			merge(enableweapons, StandardShields_Lightning);
			merge(enableweapons, StandardShields_Deep);
			merge(enableweapons, StandardShields_Dark);
			merge(enableweapons, StandardShields_Poison);
			merge(enableweapons, StandardShields_Blood);
			merge(enableweapons, StandardShields_Raw);
			merge(enableweapons, StandardShields_Blessed);
			merge(enableweapons, StandardShields_Hollow);
		}
	}

	glbl = timer;
	Thread^ myThread = gcnew Thread(gcnew ThreadStart(changeweapon));
	myThread->IsBackground = true;
	myThread->Start();
}