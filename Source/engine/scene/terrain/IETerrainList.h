/***********************************
* name     : IETerrainList.h
* creater  : cosc
* info     : all creatures manager
* date     : 2017/2/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAINS_LIST__
#define __IE_TERRAINS_LIST__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"

IE_BEGIN

typedef struct _ieTerrainInfo
{
	_ieTerrainInfo()
	{ 
		_TerrainID = 0; 
		_LuaScript = NULL; 
		_XML = NULL;
	};
	~_ieTerrainInfo()
	{ 
		__IE_LUA_RELEASE__(_LuaScript); 
		__IE_RELEASE_DIF__(_XML); 
	};

	unsigned int _TerrainID;
	char _TerrainName[64];

	lua_State * _LuaScript;
	IEXml * _XML;
}IETerrainEntry;

class __IE_DLL__ IETerrainList
{
public:
	IETerrainList();
	virtual ~IETerrainList();
	virtual void Initialization();
	virtual void Release();
	static IETerrainList * Share();

public:
	IETerrainEntry * GetEntrys();
	unsigned int GetEntrysCount();

	void AddEntry(const char * terrainName);
	void DelEntry(const char * terrainName);
	void DelEntry(unsigned int terrainID);

	void LoadList();
	void SaveList();

private:
	static IETerrainList * m_staticTerrainsManager;

	IETerrainEntry * m_entrys;
	unsigned int m_entrysCount;
};

IE_END

#endif