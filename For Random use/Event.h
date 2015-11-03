#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"

using namespace std;

typedef void (*playerActionCallback)(cPlayer& rPlayer, void* pData);
typedef bool (*eventCondition)(cPlayer& rPlayer);

enum eActionEvent
{
	AC_ERROR,
	// Money
	AC_MoneyChange,
	AC_MoneySet,

	// Save // System
	AC_Save,
	AC_SPause,
	AC_SCLS,
	AC_SSkype,

	// Shell Execute 
	AC_SERedditFunny,

	// Belogings // Stats // Feelings // Fetishes
	AC_Gender,
	AC_Belogings,
	AC_Stats,
	AC_Feeling,
	AC_Fetish
};
enum eActionEventReturns
{
	ACR_Nothing,
	ACR_Value,
	ACR_SParam,
	ACR_BParam,

	//add in before this 
	ACR_Error
};

class cBaseEvent
{
public:
	cBaseEvent() {};
	virtual ~cBaseEvent() {};

	virtual void ExcecuteEvent(cPlayer& rPlayer);
	virtual void ReadEvent(ifstream& in);
};

class cEventSequence : public cBaseEvent
{
public:
	~cEventSequence();

	void ExcecuteEvent(cPlayer& rPlayer);
	void ReadEvent(ifstream& in);

	vector<cBaseEvent*> m_events;
};

class cTextEvent : public cBaseEvent
{
public:
	void ExcecuteEvent(cPlayer& rPlayer);
	void ReadEvent(ifstream& in);

	vector<string> m_textLines;
};

class cActionEvent : public cBaseEvent
{
public:
	~cActionEvent();

	void ExcecuteEvent(cPlayer& rPlayer);
	void ReadEvent(ifstream& in);

	playerActionCallback m_actionCallback;
	void* m_callBackData = NULL;

private:
	void ReadValue(ifstream& in);
	void ReadStatsParam(ifstream& in);
	void ReadBelogingsParam(ifstream& in);

	eActionEvent ACToEnum(string eventType);
	int GetIndex(string stringIndex);
};

class cConditionEvent : public cBaseEvent
{
public:
	~cConditionEvent();
	void ExcecuteEvent(cPlayer& rPlayer);
	void ReadEvent(ifstream& in);

	eventCondition m_condition;
	cBaseEvent* m_eventIfTrue = NULL;
	cBaseEvent* m_eventIfFalse = NULL;

private:
	void tmpEventCondition(string condition);
};