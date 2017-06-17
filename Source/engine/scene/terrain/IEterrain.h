/***********************************
* name     : IEterrain.h
* creater  : cosc
* info     : terrain
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN__
#define __IE_TERRAIN__

#include "../base/IEarea.h"
#include "IEterrainBlock.h"
#include "IEterrainsInfoManager.h"

IE_BEGIN

typedef struct ieTerrainAlterInfo
{
	unsigned int _TerrainID;
	IETerrainMode _TerrainMode;
	unsigned int _Order;
}IETerrainAlterInfo;

class IETerrainAlter:public IEObject
{
public:
	int _X;
	int _Y;

	int _chunkLocationX;
	int _chunkLocationY;
	int _explicitBlockLocationX;
	int _explicitBlockLocationY;

	IETerrainAlterInfo _TerrainInfo;
	IETerrainAlterInfo _TerrainInfoOld;
};

class __IE_DLL__ IETerrain :public IEArea
{
public:
	IETerrain();
	virtual ~IETerrain();
	virtual void Initialization(IEMap * map, int halfViewBlocks, int blockSize);
	static IETerrain * Create(IEMap * map, int halfViewBlocks, int blockSize);

public:
	virtual void AddChild(unsigned int terrainID, IETerrainMode terrainMODE, int blockLocationX, int blockLocationY);
	virtual void RemoveChild(int posiWorldX, int posiWorldY);

	virtual void LoadChild(int chunkLocationX, int chunkLocationY, IETerrainBlockFormat * blocks);

	virtual void RollbackAlters();
	virtual void RollbackAlter();

private:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

	void LoadBody(IETerrainBlock * block, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);
	void LoadNone(IETerrainBlock * block, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);

	void AddBody(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyBevel(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyPiece(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyNone(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);

private:
	IETerrainInfo * m_terrainsInfo;
	IETerrainAlter * m_alter;

	unsigned int m_choosedTerrainID;
	IETerrainMode m_choosedTerrainMODE;

	//避免字符串拼接所带来的开销
	char * m_loadString[4];
	char stringBody[16];
	char stringBorder[16];
	char stringNumber[16];
	char stringPNG[16];

	friend class IEMap;
};

IE_END

#endif