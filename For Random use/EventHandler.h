#pragma once

#include "Event.h"

//////////////////////// MONEY /////////////////////////
void PlayerMoneyChangeEvent(cPlayer& rPlayer, void* pData);
void PlayerMoneySetEvent(cPlayer& rPlayer, void* pData);

/////////////////////// SYSTEM / SAVE /////////////////
void PlayerSaveEvent(cPlayer& rPlayer, void* pData);
void PlayerSCLSEvent(cPlayer&, void* pData);
void PlayerSPauseEvent(cPlayer&, void* pData);
void PlayerSSkypeEvent(cPlayer&, void* pData);

////////////////////// Shell execute //////////////////
void PlayerSERedditFunny(cPlayer&, void* pData);

////////////////////// BELOGINGS /////////////////////
void PlayerBelogingsEvent(cPlayer& rPlayer, void* pData);

///////////////////// STATS //////////////////////////
void PlayerStatEvent(cPlayer& rPlayer, void* pData);
void PlayerFeelingEvent(cPlayer& rPlayer, void* pData);

//////////////////// CONDITIONS /////////////////////
bool PlayerEventGfProbCond(cPlayer& rPlayer);
bool PlayerCityFunCond(cPlayer& rPlayer);
bool TheUncertaintyCond(cPlayer& rPlayer);
bool testCond(cPlayer& rPlayer);

///////////////////// Fetish ////////////////////////
void PlayerFetishEvent(cPlayer& rPlayer, void* pData);

class cEventHandler
{
public:
	cEventHandler() {};
	~cEventHandler();

	void Initialize();
	void ExecuteEvent(size_t eventNumber, cPlayer& rPlayer);
	void ReadEvent(string Filepath);

	vector<cBaseEvent*> m_eventSequences;
};

struct sBelogingsParam
{
	int index;
	bool value;
};
struct sStatsParam
{
	int index;
	int value;
};
struct sEventData
{
	string Name;
	int eventC = 0;
	int textC = 0;
	int actionC = 0;
	vector <string> eventOrder;
};