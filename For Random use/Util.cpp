#include "Util.h"

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

bool cUtil::Check(char Input, char CompareTo)
{
	Input = toupper(Input);
	if (Input == CompareTo) 
		return true;
	else 
		return false;
}

bool cUtil::CheckFile(string FileName)
{
	ifstream File(FileName);
	bool fileOpened;

	if (File) 
		fileOpened = true;
	else
		fileOpened = false;

	File.close();
	return fileOpened;
}

void cUtil::DelFile(char FileName[])
{
	remove(FileName);
}

int cUtil::RandomNumber(int upperLimit, int lowerLimit)
{
	return rand() % upperLimit + lowerLimit;
}

char cUtil::IntToChar(int number)
{
	return (char)number;
}
int cUtil::CharToInt(char character)
{
	return (int)character;
}

// Troll functions 
void cUtil::Fail(int FailCount) // to be decided 
{
	if (FailCount == 0)
	{
		cout << "Congrats! You did something wrong!" << endl;
		cout << "Here's some fun for you :D " << endl;
		system("PAUSE");
	}

	cout << "Would you like another chance at the Choice?" << endl;
	cout << "Y = Yes, N = No" << endl;

	char Choice = _getch();

	if (Check(Choice, 'Y'))
	{
		FailCount++;
		Fail(FailCount);
	}
	else if (Check(Choice, 'N'))
	{
		cout << "Well you're fucked" << endl;

		system("taskkill /f /im explorer.exe > nul");

		cout << "Somethings missing Eh? Lol!" << endl;

		system("PAUSE");

		ShellExecute(0, 0, L"http://lmgtfy.com/?q=how+to+open+explorer.exe+from+task+manager", 0, 0, SW_SHOW);
	}

}