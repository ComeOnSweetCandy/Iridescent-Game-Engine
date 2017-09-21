/***********************************
* name     : IEPropList.h
* creater  : cosc
* info     : creature
* date     : 2017/4/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP_LIST__
#define __IE_PROP_LIST__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"

IE_BEGIN

typedef struct iePropEntry
{
	int _PropID;
	char _PropName[64];

	lua_State * _LUA;
	IEXml * _XML;
}IEPropEntry;

//Creatures的信息列表
class IEPropList
{
public:
	IEPropList();
	virtual ~IEPropList();
	virtual void Initialization();
	virtual void Release();
	static IEPropList * Share();

public:
	IEPropEntry * GetEntrys();
	unsigned int GetEntrysCount();

	void AddEntry(const char * creatureName);
	void DelEntry(const char * creatureName);
	void DelEntry(unsigned int creatureID);

	void LoadList();
	void SaveList();

private:
	static IEPropList * m_staticList;

	IEPropEntry * m_entrys;
	unsigned int m_entrysCount;

	friend class IEProp;
};

IE_END

#endif