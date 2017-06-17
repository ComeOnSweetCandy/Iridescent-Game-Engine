/***********************************
* name     : IEphysicPolygon.h
* creater  : cosc
* info     : physic nodes' edge polygon
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_POLYGON__
#define __IE_PHYSIC_POLYGON__

#include "IEphysicEdge.h"

IE_BEGIN

struct IEPhysicPolygonInfo :IEPhysicEdgeInfo
{
	IEPhysicPolygonInfo()
	{

	};
	virtual ~IEPhysicPolygonInfo()
	{
		delete[]m_vertexs;
	};
	IEVector * m_vertexs;
	int m_vertexsCount;
};

class __IE_DLL__ IEPhysicPolygon :public IEPhysicEdge
{
public:
	IEPhysicPolygon();
	virtual ~IEPhysicPolygon();
	virtual void Initialization(IEPhysicEdgeInfo * physicEdgeInfo);
	static IEPhysicPolygon * Create(IEPhysicEdgeInfo * physicEdgeInfo);

public:
	virtual void DrawPhysicEdge();
	IEVector GetBarycenter();
};

IE_END

#endif