/***********************************
* name     : IEPathArea.h
* creater  : cosc
* info     : path area
* date     : 2017/4/15
* version  : 1.0
* remark   : path area which binded so much road.
************************************/

#ifndef __IE_PATH_AREA__
#define __IE_PATH_AREA__

#include "../IEArea.h"
#include "IEPathChunk.h"

IE_BEGIN

class IEPhysicNode;

class __IE_DLL__ IEPathArea :public IEArea
{
public:
	IEPathArea();
	virtual ~IEPathArea();
	virtual void Initialization(IEMap * map, int halfViewBlocks, int blockSize);
	static IEPathArea * Create(IEMap * map, int halfViewBlocks, int blockSize);

public:
	void ReckonAddPath(IEPhysicNode * physicNode);				//计算新增的physicNode将占据的通道
	void ReckonDelPath(IEPhysicNode * physicNode);				//计算去掉的physicNode将占据的通道

	void ReckonPhysicNodeDot(IEPhysicNode * physicNode, IEGrid curGrid, IEGrid curTunnelGrid);	//计算该点是否在列表内 且进行通道计算
	bool ReckonDotInPhysicNode(IEPhysicNode * physicNode, IEVector position);					//判断点是否在physicNode中

protected:
	virtual void Visit();

	virtual IEChunk * CreateChunk();

private:
	IEArray * m_list;

	friend class IEMap;
};

IE_END

#endif