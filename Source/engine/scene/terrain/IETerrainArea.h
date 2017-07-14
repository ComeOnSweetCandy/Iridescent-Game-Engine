/***********************************
* name     : IETerrainArea.h
* creater  : cosc
* info     : terrain area
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN_AREA__
#define __IE_TERRAIN_AREA__

#include "../IEArea.h"
#include "IETerrainChunk.h"
#include "IETerrainsInfoManager.h"

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

	IETerrainAlterInfo _Terrain;
	IETerrainAlterInfo _TerrainPast;
};

class __IE_DLL__ IETerrainArea :public IEArea
{
public:
	IETerrainArea();
	virtual ~IETerrainArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IETerrainArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	virtual void AddChild(int blockLocationX, int blockLocationY);										//添加一个新的child
	virtual void LoadChilds(IETerrainBlockFormat * blocks, int chunkLocationX, int chunkLocationY);		//最多一次传递过来最大快速的数据块量

	virtual void MouseMove(float x, float y);															//鼠标的移动
	virtual void MouseCancel();																			//鼠标的右键取消
	virtual void MouseClick();																			//有ready物下的一次点击
	virtual void RollbackAlter();																		//回滚一次操作
	virtual void RollbackAllAlters();																	//回滚所有的操作
	virtual void SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode);					//设定准备的terrain

private:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

	void LoadBody(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);
	void LoadNone(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);

	//void AddBody(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY){};
	void ApplyBevel(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyPiece(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyNone(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);

	//通过这四个方式创建的 index都是随机的
	void ChangeNone(int blockLocationX, int blockLocationY);
	void ChangeBody(int blockLocationX, int blockLocationY);
	void ChangeBevel(int blockLocationX, int blockLocationY) {};
	void ChangePiece(int blockLocationX, int blockLocationY) {};

private:
	IETerrainInfo * m_terrainsInfo;
	IETerrainAlter * m_alter;

	unsigned int m_choosedTerrainOrder;
	unsigned int m_readyTerrainID;
	IETerrainMode m_readyTerrainMode;

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