/***********************************
* name     : IEphysicSector.h
* creater  : cosc
* info     : physic nodes' edge polygon
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_SECTOR__
#define __IE_PHYSIC_SECTOR__

#include "IEphysicEdge.h"

IE_BEGIN

struct IEPhysicSectorInfo :IEPhysicEdgeInfo
{
	float m_radius;
	float m_angle;
	int m_vertexsCount;
};

class __IE_DLL__ IEPhysicSector :public IEPhysicEdge
{
public:
	IEPhysicSector();
	virtual ~IEPhysicSector();
	virtual void Initialization(IEPhysicEdgeInfo * physicEdgeInfo);
	static IEPhysicSector * Create(IEPhysicEdgeInfo * physicEdgeInfo);

public:
	virtual void DrawPhysicEdge();
	virtual IEVector GetBarycenter();
};

IE_END

#endif