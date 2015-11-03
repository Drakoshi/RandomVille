#include "EventHandler.h"
#include <fstream>
#include <Windows.h>
#include <atlstr.h>

//////////////////////// MONEY /////////////////////////
void PlayerMoneyChangeEvent(cPlayer& rPlayer, void* pData)
{
	rPlayer.Money += *(int*)pData;
}
void PlayerMoneySetEvent(cPlayer& rPlayer, void* pData)
{
	rPlayer.Money = *(int*)pData;
}

/////////////////////// SYSTEM / SAVE /////////////////
void PlayerSaveEvent(cPlayer& rPlayer, void* pData)
{
	rPlayer.Save();
}
void PlayerSCLSEvent(cPlayer&, void* pData)
{
	system("CLS");
}
void PlayerSPauseEvent(cPlayer&, void* pData)
{
	system("pause > nul");
}
void PlayerSSkypeEvent(cPlayer&, void* pData)
{
	//system("taskkill /f /im skype.exe > nul");
}

////////////////////// Shell execute //////////////////
void PlayerSERedditFunny(cPlayer&, void* pData)
{
	ShellExecute(0, 0, L"http://www.reddit.com/r/funny/", 0, 0, SW_SHOW);
}

////////////////////// BELOGINGS /////////////////////
void PlayerBelogingsEvent(cPlayer& rPlayer, void* pData)
{
	sBelogingsParam* tmpPtr = (sBelogingsParam*)pData;
	if (tmpPtr != NULL)
		rPlayer.Belogings[tmpPtr->index] = tmpPtr->value;
}

///////////////////// STATS //////////////////////////
void PlayerStatEvent(cPlayer& rPlayer, void* pData)
{
	sStatsParam* tmpPtr = (sStatsParam*)pData;
	if (tmpPtr != NULL)
		rPlayer.Stats[tmpPtr->index] += tmpPtr->value;
}
void PlayerFeelingEvent(cPlayer& rPlayer, void* pData)
{
	sStatsParam* tmpPtr = (sStatsParam*)pData;
	if (tmpPtr != NULL)
		rPlayer.Feelings[tmpPtr->index] += tmpPtr->value;
}
void PlayerGenderEvent(cPlayer& rPlayer, void* pData)
{
	rPlayer.Gender = *(int*)pData;
}

//////////////////// CONDITIONS /////////////////////
bool PlayerEventGfProbCond(cPlayer& rPlayer)
{
	return (rPlayer.Gender == 0 && rPlayer.Belogings[BEL_GF]);
}
bool PlayerCityFunCond(cPlayer& rPlayer)
{
	return (rPlayer.Gender == 0 && !rPlayer.Belogings[BEL_GF]);
}
bool TheUncertaintyCond(cPlayer& rPlayer)
{
	return (rPlayer.Age == 18 || rPlayer.Age == 19);
}
bool XChangeCond(cPlayer& rPlayer)
{
	return (rPlayer.Gender == 0);
}

///////////////////// Fetish ////////////////////////
void PlayerFetishEvent(cPlayer& rPlayer, void* pData)
{
	sBelogingsParam* tmpPtr = (sBelogingsParam*)pData;
	if (tmpPtr != NULL)
		rPlayer.FetishStorage[tmpPtr->index] = tmpPtr->value;
}

//////////////////////////////////////////////////////////////////////////

void cEventHandler::ReadEvent(string Filepath)
{
	ifstream in;
	in.open(Filepath);

	if (!cUtil::CheckFile(Filepath))
		cout << "FAIL!" << endl;

	cEventSequence* mainSequence = new cEventSequence();

	cTextEvent* Title = new cTextEvent();
	Title->ReadEvent(in);
	mainSequence->m_events.push_back(Title);

	mainSequence->ReadEvent(in);
	
	in.close();

	m_eventSequences.push_back(mainSequence);
}

cEventHandler::~cEventHandler()
{
	for (size_t i = 0; i < m_eventSequences.size(); ++i)
	{
		delete m_eventSequences[i];
		m_eventSequences[i] = NULL;
	}

	m_eventSequences.clear();
}

void cEventHandler::Initialize()
{
	int i = 0;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(L"Events/E*.txt", &FindFileData);

	while (hFind != INVALID_HANDLE_VALUE)
	{
		string thing = CT2A(FindFileData.cFileName); // For me CT2A has red underline as unknown, but it works ...

		// TO DO edit to be enabled when Hacks in enabled
		//cout << i << " " << thing << endl;
		ReadEvent("Events/" + thing);

		if (!FindNextFile(hFind, &FindFileData))
			break;

		i++;
	}
	FindClose(hFind);
}

void cEventHandler::ExecuteEvent(size_t eventNumber, cPlayer& rPlayer)
{
	if (eventNumber < m_eventSequences.size())
		m_eventSequences[eventNumber]->ExcecuteEvent(rPlayer);
	else
		cout << "Error: event ID is too Large" << endl;
}