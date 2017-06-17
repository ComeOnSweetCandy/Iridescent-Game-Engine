/***********************************
* name     : IEarea.h
* creater  : cosc
* info     : block manager area
* date     : 2016/12/11
* version  : 1.0
* remark   : none
************************************/
#ifndef __IE_AREA__
#define __IE_AREA__

#include "IEchunk.h"
#include "../IEmap.h"

IE_BEGIN

typedef struct ieBlockUnit
{
	IEGrid _ChunkLocation;
	IEChunk * _Chunk;
	bool _Using;
}IEBlockUnit;

class __IE_DLL__ IEArea :public IELayer
{
public:
	IEArea();
	virtual ~IEArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IEArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	virtual IEBlock * GetBlock(int blockLocationX, int blockLocationY);
	virtual IEChunk * GetChunk(int chunkLocationX, int chunkLocationY);
	IEContainer * GetAlters();

	void SetCenterChunkLocation(IEGrid centerBlock);
	void SetCenterBlockLocation(IEGrid centerWorld);

	void LocationTranslate(IEGrid blockLocation, IEGrid& chunkLocation, IEGrid& explicitBlockLocation);
	void LocationTranslate(int blockLocationX, int blockLocationY, int& chunkLocationX, int& chunkLocationY, int& explicitLocationX, int& explicitLocationY);

	IEMap * GetBindedMap();

protected:
	virtual void Visit();
	virtual IEChunk * CreateChunk();

	virtual void AddChild(IEBlock * block, int blockLocationX, int blockLocationY);		//添加子节点
	virtual void StanceChild(IEBlock * block, int blockLocationX, int blockLocationY);	//占位一个子节点
	virtual void RemoveChild(int blockLocationX, int blockLocationY);					//删除子节点

	virtual void LoadChunk(int blockX, int blockY);						//子类必须继承
	virtual void LoadChunks();
	virtual void ClearChunks();

	void SetCurOrder(unsigned int order);
	unsigned int GetCurOrder();

	bool legalRange(IEGrid chunkLocation);

private:
	void InitViewChunks();

protected:
	int m_visibleRadius;
	int m_maxBlocksCount;
	int m_sideLength;
	unsigned char m_curOrder;
	IEGrid m_centerChunkLocation;

	IEBlockUnit ** m_blocksIndex;
	IEBlockUnit *** m_blocksMatrix;
	IEContainer * m_alters;

	IEMap * m_map;

	friend class IEPathAnticipate;
	friend class IEMap;
};

IE_END

#endif