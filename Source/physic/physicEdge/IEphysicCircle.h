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
#include "../../type/IEstring.h"

IE_BEGIN

class __IE_DLL__ IEPhysicCircle :public IEPhysicEdge
{
public:
	IEPhysicCircle();
	virtual ~IEPhysicCircle();
	virtual void Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos);
	static IEPhysicCircle * Create(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos);

	virtual void Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY, float radius);
	static IEPhysicCircle * Create(IEEdgeType edgeType, float barycenterX, float barycenterY, float radius);

public:
	virtual void DrawPhysicEdge();

	void SetRadius(float radius);
	float GetRadius();

private:
	void SetRadius(IEString * infos);

private:
	float m_radius;					//半径
	int m_vertexsNum;				//涉及到绘制精度问题 除了绘制以外没有太大实际用处

	friend class IEPhysicEdgeCollision;
};

IE_END

#endif