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

#pragma pack(push)
#pragma pack(1)
typedef struct
{
	unsigned int _ThingID;
	unsigned char _X;
	unsigned char _Y;
	unsigned short _Mask;				//16位 用来标记4*4的方格
}IEAdorningOccupyInfo;

typedef struct _ieThingInfo
{
	_ieThingInfo()
	{
		_ThingID = 0;
		_LuaScript = NULL;
		_XML = NULL;
	};
	~_ieThingInfo()
	{ 
		__IE_LUA_RELEASE__(_LuaScript);
		__IE_RELEASE_DIF__(_XML);
	};

	unsigned int _ThingID;
	char _ThingName[256];

	unsigned short _OccupyCount;
	IEAdorningOccupyInfo * _OccupyInfo;

	lua_State * _LuaScript;
	IEXml * _XML;
}IEThingEntry;
#pragma pack(pop)

class IEAdorningsInfoManager
{
public:
	IEAdorningsInfoManager();
	virtual ~IEAdorningsInfoManager();
	virtual void Initialization();
	virtual void Release();
	static IEAdorningsInfoManager * Share();

public:
	void LoadAdorningsInfo();
	void SaveAdorningsInfo();

	//添加一个新的
	void AddAdorningInfo();
	void DeleteAdorningInfo();

	IEThingEntry * GetAdorningsInfoList();
	unsigned int GetAdorningsInfoCount();

private:
	static IEAdorningsInfoManager * m_staticAdorningsManager;

	IEThingEntry * m_entrys;
	unsigned int m_entrysCount;
};

IE_END

#endif