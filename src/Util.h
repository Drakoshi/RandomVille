#pragma once

#include <string>

using namespace std;

class cUtil
{
public:
	static bool Check(char Input, char CompareTo);
	static bool CheckFile(string FileName);
	static void DelFile(char FileName[]);
	static int RandomNumber(int UpperLimit, int LowerLimit);
	static char IntToChar(int number);
	static int CharToInt(char character);

	static void Fail(int FailCount);

	// write static to functions
};