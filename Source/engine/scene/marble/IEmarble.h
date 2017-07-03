/***********************************
* name     : IEmarble.h
* creater  : cosc
* info     : marble
* date     : 2017/5/3
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MARBLE__
#define __IE_MARBLE__

#include "../IEArea.h"
#include "IEmarbleBlock.h"
#include "IEmarblesInfoManager.h"

IE_BEGIN

typedef struct ieMarbleAlterInfo
{
	unsigned int _MarbleID;
}IEMarbleAlterInfo;

class IEMarbleAlterCache:public IEObject
{
public:
	int _X;
	int _Y;
	IEMarbleAlterInfo _MarbleInfo;
	IEMarbleAlterInfo _MarbleInfoOld;
};

class __IE_DLL__ IEMarble :public IEArea
{
public:
	IEMarble();
	virtual ~IEMarble();
	virtual void Initialization(IEMap * map, int halfViewBlocks, int blockSize);
	static IEMarble * Create(IEMap * map, int halfViewBlocks, int blockSize);

public:
	virtual void AddChild(unsigned int marbleID, int gridX, int gridY);
	virtual void RemoveChild(int gridX, int gridY);

	virtual void LoadChild(int blockX, int blockY, IEMarbleAlterInfo * alterInfos);

	virtual void RollbackAlter();
	virtual void RollbackAlters();

private:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

	void ApplyBody(unsigned int marbleID, int gridX, int gridY);
	void ApplyBorder(IEMarbleGrid * grid, unsigned int marbleID, int gridX, int gridY);
	void ApplyCorner(IEMarbleGrid * grid, unsigned int marbleID, int gridX, int gridY);

private:
	IEContainer * m_marbleAlters;
	IEMarbleAlterCache * m_marbleAlter;

	friend class IEMap;
};

IE_END

#endif