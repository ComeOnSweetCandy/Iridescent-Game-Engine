/***********************************
* name     : IEphysicEdge.h
* creater  : cosc
* info     : physic nodes' edge
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_EDGE__
#define __IE_PHYSIC_EDGE__

#include "../../core/IEobject.h"
#include "../../type/IEvector.h"

IE_BEGIN

enum __IE_DLL__ IEPhysicEdgeType
{
	__edge_circle__,
	__edge_polygon__,
	__edge_sector__,
	__edge_typeCount__
};

struct IEPhysicEdgeInfo
{
	IEPhysicEdgeInfo()
	{

	};
	virtual ~IEPhysicEdgeInfo()
	{

	}
	IEPhysicEdgeType m_physicEdgeType;
};

class __IE_DLL__ IEPhysicEdge:public IEObject
{
public:
	IEPhysicEdge();
	virtual ~IEPhysicEdge();
	virtual void Initialization(IEPhysicEdgeInfo * physicEdgeInfo);
	static IEPhysicEdge * Create(IEPhysicEdgeInfo * physicEdgeInfo);

public:
	virtual void DrawPhysicEdge() = 0;
	virtual IEVector GetBarycenter() = 0;

	void SetPhysicEdgeInfo(IEPhysicEdgeInfo * physicEdgeInfo);
	IEPhysicEdgeInfo * GetPhysicEdgeInfo();
	IEPhysicEdgeType GetEdgeType();

protected:
	IEPhysicEdgeInfo * m_physicEdgeInfo;
};

IE_END

#endif