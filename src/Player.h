#pragma once

#include <string>
#include "Util.h"

using namespace std;

enum eBelongings
{
	BEL_PHONE,
	BEL_HOME,
	BEL_GF,
	BEL_BF,
	BEL_CAR,
	BEL_COUNT
};
enum eFetish
{
	FET_RED, // Red hair
	FET_ZET, // ZettaiRyouiki
	FET_COUNT
};
enum eStats
{
	STA_STR,
	STA_AGI,
	STA_STAM,
	STA_INT,
	STA_COUNT
};
enum eFeelings
{
	FEE_HAPPY,
	FEE_RAGE,
	FEE_LONELY,
	FEE_SOCIAL,
	FEE_INSANITY,
	FEE_COUNT
};

class cPlayer
{
public:
	cPlayer() {};
	~cPlayer() {};

	// Basics
	string Name;
	int Age;
	int Gender; // 0 = Male, 1 = Female (maybe more later :D )

	// Stats
	int Stats[STA_COUNT];

	// Feelings
	int Feelings[FEE_COUNT];

	// Property
	int Money;
	bool Belogings[BEL_COUNT];

	// Fetishes
	bool FetishStorage[FET_COUNT];

	// Status
	bool Loaded;
	bool AdminAcess;

	// To be added

	void Save();
	bool SaveAndQuit();

	void Load();
	void Creation();
	void TesterCheck(int Password);

	void StatsDisplay(bool p = true, bool cls = false);

private:
	void StatsBorders(int start, int fill, int end, int push);
	void StatsBasic();
	bool StatsInt(int dispArray[], int size, char index);
	bool StatsBool(bool dispArray[], int size, char index);
};