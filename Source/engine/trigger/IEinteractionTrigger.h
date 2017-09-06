/***********************************
* name     : IEinteractionTrigger.h
* creater  : cosc
* info     : trigger interaction
* date     : 2017/2/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INTERACTION_TRIGGER__
#define __IE_INTERACTION_TRIGGER__

#include "IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IEInteractionTrigger :public IETrigger
{
public:
	IEInteractionTrigger();
	virtual ~IEInteractionTrigger();
	virtual void Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IEInteractionTrigger * Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

protected:
	virtual void Collision(IEPhysicNode * physicNode);

public:
	IETrigger * m_trigger;
};

IE_END

#endif