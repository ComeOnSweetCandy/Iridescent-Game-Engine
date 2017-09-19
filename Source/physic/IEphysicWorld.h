/***********************************
* name     : IEphysicWorld.h
* creater  : cosc
* info     : physic world
* date     : 2016/12/9
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_WORLD__
#define __IE_PHYSIC_WORLD__

#include "IEphysicEdgeCollision.h"

IE_BEGIN

class IENode;
class IEContainer;

class __IE_DLL__ IEPhysicWorld:public IEObject
{
public:
	IEPhysicWorld();
	virtual ~IEPhysicWorld();
	virtual void Initialization();
	static IEPhysicWorld * Create();
	
public:
	virtual void Run();
	virtual void Draw();

	void SetDisplayPhysicNode(bool displayPhysicNode);
	bool GetDisplayPhysicNode();

private:
	void AddPhysicNode(IEPhysicNode * physicNode);
	void DeletePhysicNode(IEPhysicNode * physicNode);

	void ProcessCollision(IEPhysicNode * a, IEPhysicNode * b, IEVector& N, float t);
	void ProcessOverlap(IEPhysicNode * a, IEPhysicNode * b, IEVector& xMTD);

private:
	IEContainer * m_physicNodeArrays;		//当前所有的物理体
	bool m_displayPhysicNode;				//是否显示物理体边缘
	float m_gravity;						//引力加速度

	friend class IEPhysicNode;
};

IE_END

#endif