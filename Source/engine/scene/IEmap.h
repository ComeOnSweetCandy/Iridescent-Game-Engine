/***********************************
* name     : IEMap.h
* creater  : cosc
* info     : MAP
* date     : 2017/1/20
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MAP__
#define __IE_MAP__

#include "../../core/IElayer.h"
#include "../../ai/IEpathFinder.h"

IE_BEGIN

class IETerrain;
class IEMarble;
class IEThingArea;
class IEPath;
class IEPathFinder;

//chunk存储格式
typedef struct ieChunkIndex
{
	int _X;
	int _Y;
	int _BlockOffset;
}IEChunkIndex;

//thing chunk特例存储格式
typedef struct ieThingChunkIndex
{
	int _X;
	int _Y;
	int _BlockOffset;
	ieThingChunkIndex * _Next;
}IEThingChunkIndex;

//terrain block的存储格式
typedef struct ieTerrainBlockFormat
{
	unsigned int _TerrainID;
	unsigned int  _TerrainMode;
	unsigned int _Order;
}IETerrainBlockFormat;

//marble block的存储格式
typedef struct ieMarbleBlockFormat
{
	unsigned int _MarbleID;
}IEMarbleBlockFormat;

//thing block的存储格式
#pragma pack(push)
#pragma pack(1)
typedef struct ieThingBlockFormat
{
public:
	int _X;
	int _Y;
	unsigned char _TinyX;
	unsigned char _TinyY;
	unsigned int _ThingID;
	unsigned int _Order;
	unsigned int _ExtraOrder;
	unsigned char _OperaType;
}IEThingBlockFormat;
#pragma pack(pop)

class __IE_DLL__ IEMap:public IELayer
{
public:
	IEMap();
	virtual ~IEMap();
	virtual void Initialization(char * sceneName);
	static IEMap * Create(char * sceneName);

public:
	void PreloadMap();
	void LoadMap();
	void SaveMap();

	void SaveTerrain();
	void SaveMarble();
	void SaveThing();

	void LoadTerrainChunkIndex();
	void LoadMarbleChunkIndex();
	void LoadThingChunkIndex();

	void LoadTerrainChunk(int chunkLocationX, int chunkLocationY);
	void LoadMarbleChunk(int chunkLocationX, int chunkLocationY);
	void LoadThingChunk(int chunkLocationX, int chunkLocationY);

	IEPath * GetPath();
	IETerrain * GetTerrain();
	IEMarble * GetMarble();
	IEThingArea * GetThing();

	void BuildPath(IEPhysicNode * physicNode);
	IEArray * FindPath(IEPhysicNode * physicNode, IEVector staPosition, IEVector endPosition);

protected:
	virtual void Update();

private:
	void InitAreaFile(IEString &fileName);

private:
	int m_chunkSideLength;				//一个chunk的长度
	int m_unitChunkBlockCount;			//一个chunk中包含有多少个block
	int m_visibleRadius;				//最大的可视半径
	int m_terrainBlockSize;				//在地图存储文件中 一个terrain block占据的大小
	int m_marbleBlockSize;				//在地图存储文件中 一个marble block占据的大小
	int m_thingBlockSize;				//在地图存储文件中 一个thing block占据的大小

	IETerrain * m_curTerrain;
	IEChunkIndex * m_terrainChunksIndex;
	unsigned int m_terrainIndexCount;
	unsigned int m_terrainOrder;
	IETerrainBlockFormat * m_terrainBlocksList;
	FILE * m_terrainIndexFile;
	FILE * m_terrainFile;

	IEMarble * m_curMarble;
	IEChunkIndex * m_marbleChunksIndex;
	unsigned int m_marbleIndexCount;
	unsigned int m_marbleOrder;
	IEMarbleBlockFormat * m_marbleBlocksList;
	FILE * m_marbleIndexFile;
	FILE * m_marbleFile;

	IEThingArea * m_curThing;
	IEThingChunkIndex * m_thingChunksIndex;
	unsigned int m_thingIndexCount;
	unsigned int m_thingOrder;
	IEThingBlockFormat * m_thingBlocksList;
	FILE * m_thingIndexFile;
	FILE * m_thingFile;

	IEPath * m_curPath;
	IEPathFinder * m_pathFinder;

	IEString m_sceneName;
	IEString m_sceneTerrainName;
	IEString m_sceneMarbleName;
	IEString m_sceneThingName;
};

IE_END

#endif