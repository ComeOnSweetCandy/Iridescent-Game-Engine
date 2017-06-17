/***********************************
* name     : IEpath.h
* creater  : cosc
* info     : terrain
* date     : 2017/4/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PATH__
#define __IE_PATH__

#include "../base/IEarea.h"
#include "IEpathBlock.h"

IE_BEGIN

class IEPhysicNode;

class __IE_DLL__ IEPath :public IEArea
{
public:
	IEPath();
	virtual ~IEPath();
	virtual void Initialization(IEMap * map, int halfViewBlocks, int blockSize);
	static IEPath * Create(IEMap * map, int halfViewBlocks, int blockSize);

public:
	virtual void Visit();

	void ReckonPath(IEPhysicNode * physicNode);
	void RecoverPhysicNodeRange(IEPhysicNode * phsyicNode);
	void ReckonPhysicNodeDot(IEPhysicNode * physicNode, IEGrid curGrid, IEGrid curTunnelGrid);
	bool ReckonDotInPhysicNode(IEPhysicNode * physicNode, IEVector position);

protected:
	IEChunk * CreateChunk();

private:
	IEArray * m_list;

	friend class IEMap;
};

IE_END

#endif