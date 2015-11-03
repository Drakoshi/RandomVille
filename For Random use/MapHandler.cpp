#include "MapHandler.h"
#include "Util.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>

bool cMapHandler::GetMap(string mapPath)
{
	ifstream in;
	in.open(mapPath);

	if (!MapOpen(mapPath))
	{
		cout << "No map" << endl; // make into message box 
		return false;
	}

	in >> mapSize.x;
	in >> mapSize.y;

	SetConsoleOutputCP(437);

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			int charCode;
			in >> charCode;

			char symChar = cUtil::IntToChar(charCode);

			Map.push_back(symChar);
		}
	}
	
	return true;
}
bool cMapHandler::MapOpen(string gFilePath)
{
	bool fileOpen = cUtil::CheckFile(gFilePath);

	// Make this Error message into a function for more usage
	wstring Msg = L"Map is missing! \nCheck Files, ask creator for map! \nRetry? ";

	if (!fileOpen)
	{
		int MsgBoxID = MessageBox(nullptr, Msg.c_str(), TEXT("Error"), MB_YESNO | MB_ICONERROR);

		if (MsgBoxID == IDYES)
			return MapOpen(gFilePath);

		else if (MsgBoxID == IDNO)
			return false;
	}
	else
		return true;

	return false;
}

// make a screen out of this or implement this into something else to display everything i need
void cMapHandler::DisplayMap(bool p, bool cls)
{
	if (cls)
		system("CLS");

	cout << "Map:"<< endl;

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
			cout << Map[GetCord(x, y, mapSize.x)];		

		if (mapSize.x != 80)
			cout << endl;
	}

	if (p)
		system("Pause > nul");
}
void cMapHandler::DisplayPartOfMap(int xPos,int yPos,int radius)
{
	cout << cUtil::IntToChar(201);
	for (int x = xPos - radius + 1; x < xPos + radius; x++)
		cout << cUtil::IntToChar(205);
	cout << cUtil::IntToChar(187) << endl;

	for (int y = yPos - radius + 1; y < yPos + radius; y++)
	{
		cout << cUtil::IntToChar(186);

		for (int x = xPos - radius + 1; x < xPos + radius; x++)
		{
			if (y < 0 || x < 0 || y > mapSize.y - 1 || x > mapSize.x - 1)
				cout << cUtil::IntToChar(176);
			else
				cout << Map[GetCord(x, y, mapSize.x)];
		}

		cout << cUtil::IntToChar(186) << endl;
	}

	cout << cUtil::IntToChar(200);
	for (int x = xPos - radius + 1; x < xPos + radius; x++)
		cout << cUtil::IntToChar(205);
	cout << cUtil::IntToChar(188) << endl;
}

int cMapHandler::GetCord(int x, int y, int size)
{
	return x + y*size;
}

void cMapHandler::PlaceEvent(int& eCount)
{
	sPoint eventPoint;
	eventPoint.x = cUtil::RandomNumber(10, 0);
	eventPoint.y = cUtil::RandomNumber(10, 0);

	// There used to be 2x FOR loops for ... unknown reason 
	if (Map.at(GetCord(eventPoint.x, eventPoint.y, mapSize.x)) == ' ')
	{
		Map.at(GetCord(eventPoint.x, eventPoint.y, mapSize.x)) = 'E';
		eCount++;
	}				
	else
	{
		bool changed = true;
		CheckChangeAround(eventPoint.x, eventPoint.y, ' ', changed);
		if(changed)
		{
			Map.at(GetCord(eventPoint.x, eventPoint.y, mapSize.x)) = 'E';
			eCount++;
		}
	}
}

void cMapHandler::CheckChangeAround(int& x, int& y, char target, bool& changed)
{
	int CX = x;
	int CY = y;

	bool up = (y - 1 >= 0) ? true : false;
	bool down = (y + 1 < mapSize.y) ? true : false;

	bool left = (x - 1 >= 0) ? true : false;
	bool right = (x + 1 < mapSize.x) ? true : false;

	// RANDOMIZE THE SIDE ITS GETTING PUT TO

	if (up)
		if (Map.at(GetCord(x, y - 1, mapSize.x)) == target)
			y--;

	else if (down)
		if (Map.at(GetCord(x, y + 1, mapSize.x)) == target)
			y++;

	else if (left)
		if (Map.at(GetCord(x - 1, y, mapSize.x)) == target)
			x--;

	else if (right)
		if (Map.at(GetCord(x + 1, y, mapSize.x)) == target)
			x++;

	if (CX == x && CY == y)
		changed = false;
}

// move elsewhere?
void cMapHandler::FindObject(int& X,int& Y,char target) 
{
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			if (Map.at(GetCord(x, y, mapSize.x)) == target)
			{
				X = x;
				Y = y;
			}
		}
	}
}

void cMapHandler::Movement(char choice,char& lastSpot)
{
	int iChoice = (int)choice;

	switch (iChoice)
	{
	case KEY_UP:
		if (DirectionAvailable(playerCord.x, playerCord.y, 0, -1))
			lastSpot = playerMapMove(playerCord.x, playerCord.y, 0, -1, lastSpot);
		break;
	case KEY_DOWN:
		if (DirectionAvailable(playerCord.x, playerCord.y, 0, 1))
			lastSpot = playerMapMove(playerCord.x, playerCord.y, 0, 1, lastSpot);
		break;
	case KEY_LEFT:
		if (DirectionAvailable(playerCord.x, playerCord.y, -1, 0))
			lastSpot = playerMapMove(playerCord.x, playerCord.y, -1, 0, lastSpot);
		break;
	case KEY_RIGHT:
		if (DirectionAvailable(playerCord.x, playerCord.y, 1, 0))
			lastSpot = playerMapMove(playerCord.x, playerCord.y, 1, 0, lastSpot);
		break;
	default:
		break;
	}
}
bool cMapHandler::DirectionAvailable(int x, int y, int xMod, int yMod)
{
	bool xMove = (x + xMod >= 0 && x + xMod < mapSize.x) ? true : false;
	bool yMove = (y + yMod >= 0 && y + yMod < mapSize.y) ? true : false;

	if (xMove && yMove)
		return Map.at(GetCord(x + xMod, y + yMod, mapSize.x)) == ' ' || Map.at(GetCord(x + xMod, y + yMod, mapSize.x)) == 'E';

	return false;
}
char cMapHandler::playerMapMove(int x, int y, int xMod, int yMod,char lastSpot)
{
	Map.at(GetCord(x, y, mapSize.x)) = lastSpot;
	lastSpot = Map.at(GetCord(x + xMod, y + yMod, mapSize.x));
	Map.at(GetCord(x + xMod, y + yMod, mapSize.x)) = 'P';

	return lastSpot;
}