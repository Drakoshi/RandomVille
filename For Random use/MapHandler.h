#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class cMapHandler
{
public:
	cMapHandler() {};
	~cMapHandler() {};

	struct sPoint
	{
		int x = 0;
		int y = 0;
	};
	sPoint mapSize;

	sPoint playerCord;

	vector<char> Map;

	bool GetMap(string mapPath); // read in Map
	
	void DisplayMap(bool p = true, bool cls = true); // Display the map on screen
	void DisplayPartOfMap(int xPos, int yPos, int radius);

	void PlaceEvent(int& eCount); // places event in map
	
	void FindObject(int& x, int& y, char target); // finds certain object

	void Movement(char choice, char& spot); // movement around with P
	
private:
	bool MapOpen(string gfilePath);

	int GetCord(int x, int y, int size); // move into utils?

	void CheckChangeAround(int& x, int& y, char target, bool& change);

	bool DirectionAvailable(int x, int y, int xMod, int yMod);

	char playerMapMove(int x, int y, int xMod, int yMod, char spot);
};