/***********************************
* name     : IEThingList.h
* creater  : cosc
* info     : thing list
* date     : 2017/4/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_LIST__
#define __IE_THING_LIST__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"

IE_BEGIN

typedef struct
{
	unsigned int _ThingID;
	unsigned char _X;
	unsigned char _Y;
	unsigned short _Mask;				//16位 用来标记4*4的方格
}IEAdorningOccupyInfo;

typedef struct _ieThingEntry
{
	_ieThingEntry()
	{
		_ThingID = 0;
		_OccupyCount = 0;
		_OccupyInfo = NULL;
		_LUA = NULL;
		_XML = NULL;
	};
	~_ieThingEntry()
	{ 
		__IE_LUA_RELEASE__(_LUA);
		__IE_RELEASE_DIF__(_XML);
	};

	//每个thing具有唯一的ID 以及显示thing的名字
	unsigned int _ThingID;
	char _ThingName[64];

	//在网格系统中所占据的网格数据
	unsigned short _OccupyCount;
	IEAdorningOccupyInfo * _OccupyInfo;

	//脚本和XML
	lua_State * _LUA;
	IEXml * _XML;
}IEThingEntry;

class IEThingList
{
public:
	IEThingList();
	virtual ~IEThingList();
	virtual void Initialization();
	virtual void Release();
	static IEThingList * Share();

public:
	IEThingEntry * GetEntrys();
	unsigned int GetEntrysCount();

	void AddEntry(const char * thingName);
	void DelEntry(const char * thingName);
	void DelEntry(unsigned int tingID);

	void LoadList();
	void SaveList();

private:
	static IEThingList * m_stateList;

	IEThingEntry * m_entrys;
	unsigned int m_entrysCount;
};

IE_END

#endif