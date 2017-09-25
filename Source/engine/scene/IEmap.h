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
#include "../../ai/IEPathFinder.h"

IE_BEGIN

#define __MAP_EDIT_TERRAIN__	0
#define __MAP_EDIT_THING__		1

class IEArea;
class IETerrainArea;
class IEThingArea;
class IEPathArea;
class IEPathFinder;

struct IETerrainSerialization;

//chunk�洢��ʽ
typedef struct ieChunkIndex
{
	int _X;
	int _Y;
	int _BlockOffset;
}IEChunkIndex;

//thing chunk�����洢��ʽ
typedef struct ieThingChunkIndex
{
	int _X;
	int _Y;
	int _BlockOffset;
	ieThingChunkIndex * _Next;
}IEThingChunkIndex;

//thing block�Ĵ洢��ʽ
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

typedef enum __ieSceneType
{
	__ie_scene_none__,
	__ie_scene_terrain__,
	__ie_scene_thing__,
}IESceneType;

typedef enum __ieSceneEditMode
{
	__ie_sceneEdit_touch__,
	__ie_sceneEdit_brush__,
	__ie_sceneEdit_choose__
}IESceneEditMode;

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
	void SaveThing();

	void LoadTerrainChunkIndex();
	void LoadThingChunkIndex();

	void LoadTerrainChunk(int chunkLocationX, int chunkLocationY);
	void LoadThingChunk(int chunkLocationX, int chunkLocationY);

	IEPathArea * GetPath();
	IETerrainArea * GetTerrain();
	IEThingArea * GetThing();
	void SetEditArea(int __map_edit_type__);

	void BuildPath(IEPhysicNode * physicNode);
	IEArray * FindPath(IEPhysicNode * physicNode, IEVector staPosition, IEVector endPosition);

protected:
	virtual void Update();

	void InputHandle();					//����¼�����

private:
	void InitAreaFile(IEString &fileName);

private:
	IESceneType m_activeSceneType;		//��ǰ�����scene type
	IESceneEditMode m_sceneEditMode;	//��ǰscene���޸ķ�ʽ
	IEArea * m_activeArea;				//��ǰ�޸�ģʽ�� �����area

	int m_chunkSideLength;				//һ��chunk�ĳ���
	int m_unitChunkBlockCount;			//һ��chunk�а����ж��ٸ�block
	int m_visibleRadius;				//���Ŀ��Ӱ뾶
	int m_terrainBlockSize;				//�ڵ�ͼ�洢�ļ��� һ��terrain blockռ�ݵĴ�С
	int m_marbleBlockSize;				//�ڵ�ͼ�洢�ļ��� һ��marble blockռ�ݵĴ�С
	int m_thingBlockSize;				//�ڵ�ͼ�洢�ļ��� һ��thing blockռ�ݵĴ�С

	IETerrainArea * m_curTerrain;
	IEChunkIndex * m_terrainChunksIndex;
	unsigned int m_terrainIndexCount;
	unsigned int m_terrainOrder;
	IETerrainSerialization * m_terrainsSerialization;
	FILE * m_terrainIndexFile;
	FILE * m_terrainFile;

	IEThingArea * m_curThing;
	IEThingChunkIndex * m_thingChunksIndex;
	unsigned int m_thingIndexCount;
	unsigned int m_thingOrder;
	IEThingBlockFormat * m_thingBlocksList;
	FILE * m_thingIndexFile;
	FILE * m_thingFile;

	IEPathArea * m_curPath;
	IEPathFinder * m_pathFinder;

	IEString m_sceneName;
	IEString m_sceneTerrainName;
	IEString m_sceneThingName;
};

IE_END

#endif