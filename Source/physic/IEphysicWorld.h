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
	void Run();
	void SetDisplayPhysicNode(bool displayPhysicNode);
	bool GetDisplayPhysicNode();

private:
	void AddPhysicNode(IEPhysicNode * physicNode);
	void DeletePhysicNode(IEPhysicNode * physicNode);

	void ProcessCollision(IEPhysicNode * a, IEPhysicNode * b, IEVector& N, float t);
	void ProcessOverlap(IEPhysicNode * a, IEPhysicNode * b, IEVector& xMTD);

private:
	IEContainer * m_physicNodeArrays;
	bool m_displayPhysicNode;

	friend class IEPhysicNode;
};

IE_END

#endif