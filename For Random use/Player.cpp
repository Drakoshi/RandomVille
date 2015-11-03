#include "Player.h"

#include <conio.h>
#include <fstream>
#include <iostream>
#include <iomanip>

const int defaultPush = 1;

void cPlayer::Save()
{
	ofstream out("Save.txt");

	// Basics
	out << Name << endl;
	out << Age << endl;
	out << Gender << endl;

	// Simple Stats
	for (int i = 0; i < STA_COUNT; i++)
		out << Stats[i] << " ";
	out << endl;

	// Feelings
	for (int i = 0; i < FEE_COUNT; i++)
		out << Feelings[i] << " ";
	out << endl;

	// Property
	out << Money << endl;

	for (int i = 0; i < BEL_COUNT; i++)
		out << (Belogings[i] ? 1 : 0) << " ";
	out << endl;

	// Fetish
	for (int i = 0; i < FET_COUNT; i++)
		out << (FetishStorage[i] ? 1 : 0) << " "; // ternary if statement (another if)
	out << endl;

	// Status
	out << (AdminAcess ? 1 : 0) << endl;

	out.close();

	cout << "Saving was Successful!" << endl;
}
bool cPlayer::SaveAndQuit()
{
	system("CLS");

	cout << "Would you like to save?" << endl; 
	cout << "Y = yes, anything else = No" << endl;

	char choice = _getch();
	if (cUtil::Check(choice, 'Y'))
	{
		Save();
		StatsDisplay(false);

		cout << endl << "Exit?" << endl;
		cout << "Y = yes, anything else = No" << endl;

		char choice = _getch();
		if (cUtil::Check(choice, 'Y'))
			return false;
		else
			return true;
	}
	return true;
}

void cPlayer::Creation() // player
{
	cout << "User creation!" << endl;
	cout << endl;

	cout << "Please enter Name: ";
	cin >> Name;
	cout << endl;
	
	cout << "Please enter Age: ";
	cin >> Age;
	cout << endl;

	cout << "Are you M = Male or F = Female" << endl;
	char Choice = _getch();

	if (cUtil::Check(Choice, 'M')) 
		Gender = 0;
	else if (cUtil::Check(Choice, 'F')) 
		Gender = 1;

	Money += 20;
	Belogings[BEL_PHONE] = true;
	Belogings[BEL_HOME] = true;
	Save();
}

void cPlayer::Load()
{
	fstream in;
	in.open("Save.txt");

	Loaded = true;

	// Basics
	in >> Name;
	in >> Age;
	in >> Gender;

	// Simple Stats
	for (int i = 0; i < STA_COUNT; i++)
		in >> Stats[i];

	// Feelings
	for (int i = 0; i < FEE_COUNT; i++)
		in >> Feelings[i];

	// Property
	in >> Money;
	for (int i = 0; i < BEL_COUNT; i++)
		in >> Belogings[i];

	// Fetish
	for (int i = 0; i < FET_COUNT; i++)
		in >> FetishStorage[i];

	//Status
	in >> AdminAcess;

	in.close();
}

void cPlayer::TesterCheck(int Password)  // player 
{
	system("CLS");
	cout << "You have entered secret Tester/Game creators option" << endl;
	cout << "You need password to access it..." << endl;
	cout << "Enter it on your first try!" << endl;

	int TypedPassword = 0;
	cin >> TypedPassword;

	if (Password == TypedPassword)
	{
		cout << "Access Granted!" << endl;
		AdminAcess = true;
		system("PAUSE");
	}
	else
		cUtil::Fail(0);
}

void cPlayer::StatsBorders(int start, int fill, int end, int push = defaultPush)
{
	cout << setw(push) << right << cUtil::IntToChar(start);
	for (int i = 0; i < 18; ++i)
		cout << cUtil::IntToChar(fill);
	cout << cUtil::IntToChar(end) << endl;
	// make something more fancy ? to include something inside the fill
}
void cPlayer::StatsBasic()
{
	char Hline = cUtil::IntToChar(186);

	cout << setw(defaultPush) << right << Hline << " " << setw(6) << left << "Name " << setw(10) << right << Name << " " << Hline << endl;
	cout << setw(defaultPush) << right << Hline << " " << setw(6) << left << "Age " << setw(10) << right << Age << " " << Hline << endl;

	if (Gender == 0)
		cout << setw(defaultPush) << right << Hline << " " << setw(16) << left << "You are Male" << " " << Hline << endl;
	else if (Gender == 1)
		cout << setw(defaultPush) << right << Hline << " " << setw(16) << left << "You are Female" << " " << Hline << endl;
}
bool cPlayer::StatsInt(int dispArray[],int size,char index)
{
	char Hline = cUtil::IntToChar(186);

	bool printed = false;
	for (int i = 0; i < size; ++i)
	{
		if (dispArray[i] != 0)
		{
			printed = true;
			cout << setw(defaultPush) << right << Hline << " ";
			cout << setw(11) << left;

			// add more if i add more stats
			#pragma region Text to write
			if (index == 'S')
			{
				if (i == STA_STR)
					cout << "Strength";
				if (i == STA_AGI)
					cout << "Agility";
				if (i == STA_STAM)
					cout << "Stamina";
				if (i == STA_INT)
					cout << "Intellect";
			}
			else if (index == 'F')
			{
				if (i == FEE_HAPPY)
					cout << "Happiness";
				if (i == FEE_RAGE)
					cout << "Rage";
				if (i == FEE_LONELY)
					cout << "Loneliness";
				if (i == FEE_SOCIAL)
					cout << "Social";
				if (i == FEE_INSANITY)
					cout << "Insanity";
			}
			#pragma endregion

			cout << setw(5) << right << dispArray[i] << " " << Hline << endl;
		}
	}
	return printed;
}
bool cPlayer::StatsBool(bool dispArray[], int size, char index)
{
	char Hline = cUtil::IntToChar(186);

	bool printed = false;

	if (index == 'B')
		cout << setw(defaultPush) << right << Hline << " " << setw(11) << left << "Money " << setw(5) << right << Money << " " << Hline << endl;

	for (int i = 0; i < size; ++i)
	{
		if (dispArray[i] == true)
		{
			printed = true;
			cout << setw(defaultPush) << right << Hline << " ";
			cout << setw(16) << left;

			// add more if i add more stats
			#pragma region Text to write
			if (index == 'B')
			{
				if (i == BEL_PHONE)
					cout << "Phone";
				if (i == BEL_HOME)
					cout << "Home";
				if (i == BEL_GF)
					cout << "GirlFriend";
				if (i == BEL_BF)
					cout << "BoyFriend";
				if (i == BEL_CAR)
					cout << "Car";
			}
			else if (index == 'F')
			{
				if (i == FET_RED)
					cout << "RedHairFet";
				if (i == FET_ZET)
					cout << "ZettaiRyouki";
			}
			#pragma endregion

			cout << " " << Hline << endl;
		}
	}
	return printed;
}
void cPlayer::StatsDisplay(bool p, bool cls) // set in .h file to true!
{
	// make tittles for each section?
	// inside the border?
	// make in first border to display name in the middle and remove write name 

	if (cls)
		system("CLS");

	cout << "Stats:" << endl;

	StatsBorders(201, 205, 187);

	// Basics
	StatsBasic();
	StatsBorders(199, 196, 182);

	if (StatsInt(Stats, STA_COUNT, 'S'))
		StatsBorders(199, 196, 182);

	// Feelings
	if (StatsInt(Feelings, FEE_COUNT, 'F'))
		StatsBorders(199, 196, 182);

	// Property
	if (StatsBool(Belogings, BEL_COUNT, 'B'))
		StatsBorders(199, 196, 182);

	// Fetish
	bool print3 = StatsBool(FetishStorage, FET_COUNT, 'F');
	// if i add more stats 
	/*if (print3)
	StatsBorders(199, 196, 182);*/

	StatsBorders(200, 205, 188);

	if (p)
		system("PAUSE > nul");
}