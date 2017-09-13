/***********************************
* name     : IECreatureList.h
* creater  : cosc
* info     : all creatures manager
* date     : 2017/2/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURE_LIST__
#define __IE_CREATURE_LIST__

#include "IECreature.h"

IE_BEGIN

class IECreatureList
{
public:
	IECreatureList();
	virtual ~IECreatureList();
	virtual void Initialization();
	virtual void Release();
	static IECreatureList * Share();

public:
	IECreatureEntry * GetEntrys();
	unsigned int GetEntrysCount();

	void AddEntry(const char * creatureName);
	void DelEntry(const char * creatureName);
	void DelEntry(unsigned int creatureID);
	
	void LoadList();
	void SaveList();

private:
	static IECreatureList * m_staticList;

	IECreatureEntry * m_entrys;
	unsigned int m_entrysCount;

	friend class IECreature;
};

IE_END

#endif