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
#include "IETerrainList.h"

IE_BEGIN

class IETerrainAlter:public IEObject
{
public:
	IETerrainAlter(){};
	~IETerrainAlter()
	{ 
		__IE_DELETE__(_CurtTerrainInfoSerialization);
		__IE_DELETE__(_PastTerrainInfoSerialization);
	}

public:
	unsigned int _AlterOrder;
	int _X;
	int _Y;
	int _ChunkX;
	int _ChunkY;

	IETerrainSerialization * _CurtTerrainInfoSerialization;
	IETerrainSerialization * _PastTerrainInfoSerialization;
};

class __IE_DLL__ IETerrainArea :public IEArea
{
public:
	IETerrainArea();
	virtual ~IETerrainArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IETerrainArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	virtual void AddChild(int blockLocationX, int blockLocationY);											//添加一个新的child
	virtual void ChooseChild(int blockLocationX, int blockLocationY);										//选择一个child
	virtual void LoadChilds(IETerrainSerialization * blocksInfo, int chunkLocationX, int chunkLocationY);	//读取地图文件中的数据
	virtual void RemoveChild(int locationX, int locationY);

	virtual void SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode);					//设定准备的terrain
	virtual void MouseMove(float x, float y);															//鼠标的移动
	virtual void MouseCancel();																			//鼠标的右键取消
	virtual void MouseClick();																			//有ready物下的一次点击
	virtual void MouseBrush();																			//鼠标刷子

	virtual void RollbackAlter();																		//回滚一次操作
	virtual void RollbackAllAlters();																	//回滚所有的操作

protected:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

private:
	//通过这四个方式创建的 index都是随机的
	void ChangeNone(int blockLocationX, int blockLocationY);
	void ChangeBody(int blockLocationX, int blockLocationY);
	void ChangeBevel(int blockLocationX, int blockLocationY);
	void ChangePiece(int blockLocationX, int blockLocationY);

	void ReserializatioRound(int blockLocationX, int blockLocationY);									//一个body修改 重新序列化周围的border数值

private:
	IETerrainEntry * m_terrainsInfo;
	IETerrainAlter * m_alter;

	unsigned int m_choosedTerrainOrder;
	unsigned int m_readyTerrainID;
	IETerrainMode m_readyTerrainMode;

	friend class IEMap;
};

IE_END

#endif