/***********************************
* name     : IEcollisionTrigger.h
* creater  : cosc
* info     : trigger collision
* c_date   : 2017/3/27
* l_date   : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_COLLISION_TRIGGER__
#define __IE_COLLISION_TRIGGER__

#include "IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IECollisionTrigger :public IETrigger
{
public:
	IECollisionTrigger();
	virtual ~IECollisionTrigger();
	virtual void Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IECollisionTrigger * Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

public:
	virtual void Collision(IEPhysicNode * physicNode);
};

IE_END

#endif