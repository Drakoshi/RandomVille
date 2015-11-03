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
		string thing = CT2A(FindFileData.cFileName);

		cout << i << " " << thing << endl;
		ReadEvent("Events/" + thing);

		if (!FindNextFile(hFind, &FindFileData))
			break;

		i++;
	}
	FindClose(hFind);

	/*
	// X-change
	cout << "Do you know of VN(Visual novels)?" << endl;
	cout << "Yes/No ? Well I don't care :D" << endl;
	cout << "Here's a scenario from one" << endl;
	system("PAUSE > nul"); system("CLS");
	cout << "You are school student." << endl;
	cout << "Teachers asked to get something from Science class room" << endl;
	cout << "In there you take a while to find required thing" << endl;
	cout << "On the way back you spill some strange liquid on yourself" << endl;
	cout << "You quickly wash the spot." << endl;
	cout << "You wait few minutes to make sure you are fine" << endl;
	cout << "You seem okay" << endl;
	cout << "You head out of the class room, deliver the thing you were asked to get" << endl;
	cout << "Lessons were over so you head Home" << endl;
	system("PAUSE > nul"); system("CLS");
	if (PlayerD.Gender == 0) // adjust it to stats: fetishes and sstuff :D
	{
	cout << "You dream that you are a girl" << endl;
	cout << "Spending you daily life as you please" << endl;
	cout << "It's a good dream" << endl;
	system("PAUSE > nul"); system("CLS");
	cout << "Next morning... Something is different" << endl;
	cout << "Half a sleep you proceed to bathroom" << endl;
	cout << "You were about to pee when u notice that your ..." << endl;
	cout << "Manhood" << endl; // Penis or something like that change if needed
	cout << "IS GONE!" << endl;
	cout << "You touch the spot ... it's flat ... " << endl;
	cout << "You feel something wet ..." << endl;
	cout << "You keep touching it ... it feels good :)" << endl;
	cout << "Sudden realization ... I turned into a girl ..." << endl;
	cout << "You check if you have boobs ..." << endl;
	cout << "Yup they're there" << endl;
	// choice what to do maybe ( if u know what i mean) or not default u do it :D
	cout << "You enjoy the pleasure yourself ..." << endl;
	cout << "Touching you boobs, they are big and soft" << endl;
	cout << "They're perfect any man would want them" << endl;
	cout << "You slide your fingers down to your pussy" << endl;
	cout << "You slide your fingers into your pussy" << endl;
	cout << "It feels so good" << endl;
	cout << "You masturbate till you're exhausted" << endl;
	cout << "You wonder if you have your cherry..." << endl;
	cout << "And what would be the feeling of sex ..." << endl;
	cout << "But you collapse onto your bed" << endl;
	system("PAUSE > nul"); system("CLS");
	cout << "You have turned into a girl, you are quite happy about that :)" << endl;
	cout << "Your adventures of being a such girl may continue :)" << endl;
	cout << "<This effect is real it's not a joke :D>" << endl;
	PlayerD.Gender = 1;
	PlayerD.Happy += 5;
	PlayerD.Insanity++;
	}
	else
	{
	cout << "You dream that you are a boy" << endl;
	cout << "Spending you daily life as you please" << endl;
	cout << "It's a strange dream..." << endl;
	system("PAUSE > nul"); system("CLS");
	cout << "Next morning... Something is different" << endl;
	cout << "Half a sleep you proceed to bathroom" << endl;
	cout << "You were about to pee when u notice that you ..." << endl;
	cout << "Have a penis ..." << endl;
	cout << "WHAT THE FUCK?!" << endl;
	cout << "You are lost and unhappy about your state..." << endl;
	cout << "You faint onto your bed ..." << endl;
	system("PAUSE > nul"); system("CLS");
	cout << "You have turned into a boy, you are quite unhappy about that :)" << endl;
	cout << "Your adventures of being a such boy may continue :)" << endl;
	cout << "<This effect is real it's not a joke :D>" << endl;
	PlayerD.Gender = 0;
	PlayerD.Happy -= 5;
	PlayerD.Insanity+= 2;
	*/
}

void cEventHandler::ExecuteEvent(size_t eventNumber, cPlayer& rPlayer)
{
	if (eventNumber < m_eventSequences.size())
		m_eventSequences[eventNumber]->ExcecuteEvent(rPlayer);
	else
		cout << "Error: event ID is too Large" << endl;
}