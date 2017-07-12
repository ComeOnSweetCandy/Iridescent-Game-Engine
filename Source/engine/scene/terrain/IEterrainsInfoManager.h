/***********************************
* name     : IEterrainsInfoManager.h
* creater  : cosc
* info     : all creatures manager
* date     : 2017/2/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAINS_INFO_MANAGER__
#define __IE_TERRAINS_INFO_MANAGER__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"

IE_BEGIN

typedef struct _ieTerrainInfo
{
	_ieTerrainInfo(){};
	~_ieTerrainInfo(){ __IE_LUA_RELEASE__(_LuaScript); };

	unsigned int _TerrainID;
	unsigned char _BodyC;
	unsigned char _BevelC;
	unsigned char _PieceC;
	unsigned char _BorderC;
	char _TerrainName[64];

	lua_State * _LuaScript;
	IEXml * _Xml;
}IETerrainInfo;

class IETerrainsInfoManager
{
public:
	IETerrainsInfoManager();
	virtual ~IETerrainsInfoManager();
	virtual void Initialization();
	virtual void Release();
	static IETerrainsInfoManager * Share();

public:
	IETerrainInfo * GetTerrainsInfoList();
	unsigned int GetTerrainsInfoCount();

private:
	void LoadTerrainsInfo();
	void SaveTerrainsInfo();

private:
	static IETerrainsInfoManager * m_staticTerrainsManager;

	IETerrainInfo * m_terrainsInfoList;
	unsigned int m_terrainsInfoCount;
};

IE_END

#endif