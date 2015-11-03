//Includes defaults
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

// Includes mano
#include "Util.h"
#include "Player.h"
#include "MapHandler.h"
#include "EventHandler.h"

cPlayer Player;
cEventHandler gEventHandler;
cEventSequence gEventSequence;
cMapHandler Map;

bool Hacks = false;

int main()
{
	#pragma region Setups

	SetConsoleTitle(TEXT("----- Game -----"));
	SetConsoleOutputCP(437);

	HANDLE outcon = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	int currentFont = GetCurrentConsoleFontEx(outcon, false, &font);
	font.dwFontSize.X = 8;
	font.dwFontSize.Y = 12;
	SetCurrentConsoleFontEx(outcon, false, &font);

	srand((unsigned int)time(NULL));
	gEventHandler.Initialize(); 

	if (!Map.GetMap("Maps/Map.txt"))
		return 0;
	#pragma endregion
	
	#pragma region GameStartTxt

	cout << "Welcome this Game is made by Drakoshi!" << endl;
	cout << "WARNING You might read some indecent/weird/18+ rated stuff" << endl;
	cout << "The Creator is not responsible for anything that you read in here" << endl;
	cout << "You are reading this at your own risk" << endl;
	cout << "This contains slang/internet English words" << endl;
	cout << "If you don't know the meaning look it up" << endl;
	cout << "<If you find grammar mistakes let the creator know>" << endl;
	cout << endl;
	cout << "It's a game of luck." << endl;
	cout << "<If you are seeing this you are either a tester or game creator>" << endl;
	cout << "<Or a complete strangeer, recently it was uploaded to GitHub>" << endl;
	cout << "<Got an idea suggest it :D . Got a background story to suit this project?>" << endl;
	cout << "<Please let me know!>" << endl;
	cout << "Basic idea you travel around certain area" << endl;
	cout << "You get random events" << endl;
	cout << "For now it has no ending" << endl;
	cout << "<Text to be edited in future>" << endl << endl;
	cout << "Press any key to begin!";

	char Choice = _getch();
	if (Choice == 'X')
		Player.TesterCheck(6934769);
	// No longer have helper.exe ... basicly it created empty text files rdy to make events
	/*else if (Choice == 'N' && Hacks)
	{
		system("CLS");
		cout << "New E#.txt was created" << endl;
		system("helper.exe");
		system("pause > nul");
		return 0;
	}*/
		

	system("CLS");

	#pragma endregion

	#pragma region Admin/Save Check

	if (Player.AdminAcess);
	else if (cUtil::CheckFile("save.txt"))
	{
		cout << "Save found! L = Load , N = Delete and create new" << endl;
		char Choice = _getch();

		if (cUtil::Check(Choice, 'L'))
			Player.Load();
		else if (cUtil::Check(Choice, 'N'))
		{
			cUtil::DelFile("Save.txt");
			system("CLS");
			Player.Creation();
		}
		else
		{
			cUtil::Fail(0);
			return 0;
		}
	}
	else Player.Creation();
	system("CLS");

	#pragma endregion

	#pragma region Result Check

	if (Player.AdminAcess)
	{
		cout << "Welcome to Test go!" << endl;
		Player.Name = "Tester";
		Player.Age = 18;
		Player.Gender = 0;
		Player.Money = 9999;
		Player.Belogings[BEL_HOME] = true;
		// Need to fix this to be able to access every event or make adjustments to function another "if" or something or be able to modify my stats as i go 
		// set age to Wizard The internet Virgin
	}
	else if (!Player.Loaded) 
		cout << "You have successfully created User!" << endl;
	else 
		cout << "You have successfully loaded User save" << endl;

	#pragma endregion

	Player.StatsDisplay();

	#pragma region Tutorial
	system("CLS");
	cout << "In next screen u will see map" << endl;
	cout << "some basic controls:" << endl;
	cout << "Arrow keys for moving" << endl;
	cout << "5 or Enter - use(while P is on E)" << endl;
	cout << "C will show character info" << endl;
	cout << "and E or ESC will prompt save and exit" << endl;
	system("pause > nul");
	#pragma endregion

	#pragma region Main Game loop

	int TheNumber = 0;
	bool Running = true;

	char playerLastSpot = ' ';

	int eventCount = 0;
	int eventCountLimit = 2;

	while (Running)
	{
		system("CLS");

		while (eventCount != eventCountLimit)
			Map.PlaceEvent(eventCount);

		Map.FindObject(Map.playerCord.x, Map.playerCord.y, 'P');

		//Map.DisplayMap();
		Map.DisplayPartOfMap(Map.playerCord.x, Map.playerCord.y, 4);

		char Choice = _getch();
		int iChoice = cUtil::CharToInt(Choice);
		Map.Movement(Choice, playerLastSpot);

		if (playerLastSpot == 'E' && (Choice == '5' || iChoice == 13))
		{
			playerLastSpot = ' ';
			eventCount--;

			system("CLS");
			if (Player.AdminAcess)
			{
				cout << "As tester/game creator you can choose TheNumber!" << endl;
				cin >> TheNumber;
			}
			else
			{
				cout << "EVENT MODE!" << endl << endl;
				TheNumber = cUtil::RandomNumber(gEventHandler.m_eventSequences.size(), 0);
			}

			gEventHandler.ExecuteEvent(TheNumber, Player);	
			system("pause > nul");
		}
		else if (cUtil::Check(Choice, 'E') || iChoice == 27)
			Running = Player.SaveAndQuit();
		else if (cUtil::Check(Choice, 'C'))
			Player.StatsDisplay(true,true);
		else if (cUtil::Check(Choice, 'Z'))
			Map.DisplayMap(true,true);
	}

	#pragma endregion
	
	return 0;
};