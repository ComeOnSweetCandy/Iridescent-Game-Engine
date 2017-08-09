/***********************************
* name     : IEphysicCircle.h
* creater  : cosc
* info     : physic nodes' edge circle
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_CIRCLE__
#define __IE_PHYSIC_CIRCLE__

#include "IEphysicEdge.h"

IE_BEGIN

struct IEPhysicCircleInfo :IEPhysicEdgeInfo
{
	float m_radius;
	int m_vertexsCount;
	float m_offsetPosition[2];		//用于描述一个偏移值
};

class __IE_DLL__ IEPhysicCircle :public IEPhysicEdge
{
public:
	IEPhysicCircle();
	virtual ~IEPhysicCircle();
	virtual void Initialization(IEPhysicEdgeInfo * physicEdgeInfo);
	virtual void Initialization(const char * physicEdgeInfo);
	static IEPhysicCircle * Create(const char * physicEdgeInfo);
	static IEPhysicCircle * Create(IEPhysicEdgeInfo * physicEdgeInfo);

public:
	virtual void DrawPhysicEdge();
	virtual IEVector GetBarycenter();

	void SetRadius(float radius);
	float GetRadius();

	void SetOffsetPosition(float &offsetX, float &offsetY);
	float * GetOffsetPosition();
};

IE_END

#endif