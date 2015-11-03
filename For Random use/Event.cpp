#include "Event.h"
#include "EventHandler.h"

cBaseEvent* GetNextEvent(ifstream& in)
{
	string tmp;
	in >> tmp;

	cBaseEvent* newEvent = NULL;

	if (tmp == "!T")
		newEvent = new cTextEvent();
	else if (tmp == "!A")
		newEvent = new cActionEvent();
	else if (tmp == "!S")
		newEvent = new cEventSequence();
	else if (tmp == "!C")
		newEvent = new cConditionEvent();
	else
		return NULL;

	return newEvent;
}

void cBaseEvent::ExcecuteEvent(cPlayer& rPlayer)
{
	cout << "Base Class, Do Not Use" << endl;
}
void cBaseEvent::ReadEvent(ifstream& in)
{
	cout << "Base Class, Do Not Use" << endl;
}

///////////////////// Event /////////////////////
void cEventSequence::ExcecuteEvent(cPlayer& rPlayer)
{
	for (auto& evnt : m_events)
		evnt->ExcecuteEvent(rPlayer);
}
cEventSequence::~cEventSequence()
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		if (m_events[i] != NULL) 
		{
			delete m_events[i]; 
			m_events[i] = NULL; 
		}
	}
}
void cEventSequence::ReadEvent(ifstream& in/*,string target*/)
{
	string tmp;

	while (true)
	{
		cBaseEvent* newEvent = GetNextEvent(in);
		if (newEvent != NULL)
		{
			newEvent->ReadEvent(in);
			m_events.push_back(newEvent);
		}
		else
			break;
	}
}

//////////////////// Text ///////////////////////
void cTextEvent::ExcecuteEvent(cPlayer& rPlayer)
{
	for (unsigned int i = 0; i < m_textLines.size(); ++i)
	{
		cout << m_textLines[i] << endl;
	}
}
void cTextEvent::ReadEvent(ifstream& in)
{
	string textLine;
	getline(in, textLine);
	while (textLine != "#T")
	{
		if (textLine.length() > 0)
			m_textLines.push_back(textLine);
		getline(in, textLine);
	}
}

/////////////////// ACTION /////////////////////
cActionEvent::~cActionEvent()
{
	if (m_callBackData != NULL)
	{
		delete m_callBackData;
		m_callBackData = NULL;
	}
}
void cActionEvent::ExcecuteEvent(cPlayer& rPlayer)
{
	if (m_actionCallback != NULL)
		m_actionCallback(rPlayer, m_callBackData);
}
void cActionEvent::ReadEvent(ifstream& in) // fix this
{
	string actionName;
	in >> actionName;

	eActionEvent myEnum = ACToEnum(actionName);

	switch (myEnum)
	{
	case AC_ERROR:
		break;
	case AC_MoneyChange:
		this->m_actionCallback = &PlayerMoneyChangeEvent;
		ReadValue(in);
		break;
	case AC_MoneySet:
		this->m_actionCallback = &PlayerMoneySetEvent;
		ReadValue(in);
		break;
	case AC_Save:
		this->m_actionCallback = &PlayerSaveEvent;
		break;
	case AC_SPause:
		this->m_actionCallback = &PlayerSPauseEvent;
		break;
	case AC_SCLS:
		this->m_actionCallback = &PlayerSCLSEvent;
		break;
	case AC_SSkype:
		this->m_actionCallback = &PlayerSSkypeEvent;
		break;
	case AC_SERedditFunny:
		this->m_actionCallback = &PlayerSERedditFunny;
		break;
	case AC_Belogings:
		ReadBelogingsParam(in);
		this->m_actionCallback = &PlayerBelogingsEvent;
		break;
	case AC_Stats:
		ReadStatsParam(in);
		this->m_actionCallback = &PlayerStatEvent;
		break;
	case AC_Feeling:
		ReadStatsParam(in);
		this->m_actionCallback = &PlayerFeelingEvent;
		break;
	case AC_Fetish:
		ReadBelogingsParam(in);
		this->m_actionCallback = &PlayerFetishEvent;
		break;
	case AC_Gender:
		this->m_actionCallback = &PlayerGenderEvent;
		ReadValue(in);
		break;
	default:
		break;
	}
}

void cActionEvent::ReadValue(ifstream& in)
{
	int num = 0;
	in >> num;
	this->m_callBackData = (void*)new int(num);
}
void cActionEvent::ReadStatsParam(ifstream& in)
{
	sStatsParam* actionEventParam = new sStatsParam;
	string rawIndex;
	in >> rawIndex;
	actionEventParam->index = GetIndex(rawIndex);
 
	in >> actionEventParam->value;

	this->m_callBackData = (void*)actionEventParam;
}
void cActionEvent::ReadBelogingsParam(ifstream& in)
{
	sBelogingsParam* actionEventParam = new sBelogingsParam;
	string rawIndex;
	in >> rawIndex;
	actionEventParam->index = GetIndex(rawIndex);

	in >> actionEventParam->value;
	this->m_callBackData = (void*)actionEventParam;
}

eActionEvent cActionEvent::ACToEnum(string eventType)
{
	// Money
	if (eventType == "AMonC")
		return AC_MoneyChange;
	if (eventType == "AMonS")
		return AC_MoneySet;

	// Save // System
	if (eventType == "ASave")
		return AC_Save;
	if (eventType == "ASPause")
		return AC_SPause;
	if (eventType == "ASCLS")
		return AC_SCLS;
	if (eventType == "ASSkype")
		return AC_SSkype;

	// Shell Execute 
	if (eventType == "ASERedditFunny")
		return AC_SERedditFunny;

	// Belogings // Stats // Feelings // Fetishes
	if(eventType == "AGender")
		return AC_Gender;
	if (eventType == "ABelogings")
		return AC_Belogings;
	if (eventType == "AStats")
		return AC_Stats;
	if (eventType == "AFeelings")
		return AC_Feeling;
	if (eventType == "AFetish")
		return AC_Fetish;

	return AC_ERROR;
}
int cActionEvent::GetIndex(string stringIndex)
{
	if (stringIndex == "Phone")
		return BEL_PHONE;
	if (stringIndex == "Home")
		return BEL_HOME;
	if (stringIndex == "GF")
		return BEL_GF;
	if (stringIndex == "BF")
		return BEL_BF;
	if (stringIndex == "Car")
		return BEL_CAR;

	/////////////////////////
	if (stringIndex == "RedHair")
		return FET_RED;
	if (stringIndex == "ZettaiRyouiki")
		return FET_ZET;

	////////////////////////
	if (stringIndex == "STR")
		return STA_STR;
	if (stringIndex == "AGI")
		return STA_AGI;
	if (stringIndex == "INT")
		return STA_INT;
	if (stringIndex == "STAM")
		return STA_STAM;

	/////////////////////////
	if (stringIndex == "Happiness")
		return FEE_HAPPY;
	if (stringIndex == "Rage")
		return FEE_RAGE;
	if (stringIndex == "Loneliness")
		return FEE_LONELY;
	if (stringIndex == "Social")
		return FEE_SOCIAL;
	if (stringIndex == "Insanity")
		return FEE_INSANITY;

	return -1;
}

////////////////// CONDITION //////////////////
cConditionEvent::~cConditionEvent()
{
	if (m_eventIfTrue != NULL)
	{
		delete m_eventIfTrue;
		m_eventIfTrue = NULL;
	}
	if (m_eventIfFalse != NULL)
	{
		delete m_eventIfFalse;
		m_eventIfFalse = NULL;
	}
}
void cConditionEvent::ExcecuteEvent(cPlayer& rPlayer)
{
	if (m_condition != NULL)
	{
		if (m_condition(rPlayer))
		{
			if (m_eventIfTrue != NULL)
				m_eventIfTrue->ExcecuteEvent(rPlayer);
		}		
		else
		{
			if (m_eventIfFalse != NULL)
				m_eventIfFalse->ExcecuteEvent(rPlayer);
		}
	}
}
void cConditionEvent::ReadEvent(ifstream& in)
{
	// Reads condition .... This is the lazy way of doing it :| I will get to it sometime ...

	// TO DO: must make this into proper conditions which could be written in txt FILE!

	string condition;
	in >> condition;
	tmpEventCondition(condition);

	string Type;
	in >> Type;

	if (Type == "True")
	{
		m_eventIfTrue = GetNextEvent(in);
		m_eventIfTrue->ReadEvent(in);
	}
	
	in >> Type;

	if (Type == "False")
	{
		m_eventIfFalse = GetNextEvent(in);
		m_eventIfFalse->ReadEvent(in);
	}

}
void cConditionEvent::tmpEventCondition(string condition)
{
	if (condition == "GFProb")
		m_condition = &PlayerEventGfProbCond;
	if (condition == "CityFun")
		m_condition = &PlayerCityFunCond;
	if (condition == "TheUncert")
		m_condition = &TheUncertaintyCond;
	if (condition == "XChange")
		m_condition = &XChangeCond;
}