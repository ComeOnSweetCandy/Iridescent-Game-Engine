/***********************************
* name     : IEthingsInfoManager.h
* creater  : cosc
* info     : things info manager
* date     : 2017/4/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THINGS_INFO_MANAGER__
#define __IE_THINGS_INFO_MANAGER__

#include "../../../global/IEstdafx.h"

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

typedef struct ieAdorningInfo
{
	ieAdorningInfo(){};
	~ieAdorningInfo(){ __IE_LUA_RELEASE__(_LuaScript); };

	unsigned int _ThingID;
	char _ThingName[256];

	unsigned short _OccupyCount;
	IEAdorningOccupyInfo * _OccupyInfo;

	lua_State * _LuaScript;
}IEAdorningInfo;
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

	IEAdorningInfo * GetAdorningsInfoList();
	unsigned int GetAdorningsInfoCount();

private:
	static IEAdorningsInfoManager * m_staticAdorningsManager;

	IEAdorningInfo * m_adorningsInfoList;
	unsigned int m_adorningsInfoCount;
};

IE_END

#endif