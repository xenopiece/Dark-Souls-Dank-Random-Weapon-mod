#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <msclr\marshal_cppstd.h>

void printDBG(std::string msg)
{
	std::ofstream myfile;
	myfile.open("debug.txt");
	myfile << msg << "\n";
	myfile.close();
}

void printDBG(int num)
{
	printDBG(std::to_string(num));
}

void somefunction(int timer, std::vector<std::string> stuff) 
{
/*
stuff:
L"Standard weapons (daggers, swords, etc.)",
L"Bows", L"Whips", L"Shields", L"SECRET", 
L"Heavy infusions", L"Sharp infusions", 
L"Refined infusions", L"Simple infusions",
L"Crystal infusions", L"Fire infusions", 
L"Chaos infusions", L"Lightning infusions", 
L"Deep infusions", L"Dark infusions", 
L"Poison infusions", L"Blood infusions", 
L"Raw infusions", L"Blessed infusions", 
L"Hollow infusions"
*/

}