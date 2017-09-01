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

typedef struct _ieTerrainEntry
{
	_ieTerrainEntry()
	{ 
		_TerrainID = 0; 
		_LUA = NULL; 
		_XML = NULL;
	};
	~_ieTerrainEntry()
	{ 
		__IE_LUA_RELEASE__(_LUA); 
		__IE_RELEASE_DIF__(_XML); 
	};

	unsigned int _TerrainID;
	char _TerrainName[64];

	lua_State * _LUA;
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
	static IETerrainList * m_staticList;

	IETerrainEntry * m_entrys;
	unsigned int m_entrysCount;
};

IE_END

#endif