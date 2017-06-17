/***********************************
* name     : IEbesiegeTrigger.h
* creater  : cosc
* info     : trigger besiege
* c_date   : 2017/5/17
* l_date   : 2017/5/17
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_BESIEGE_TRIGGER__
#define __IE_BESIEGE_TRIGGER__

#include "IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IEBesiegeTrigger :public IETrigger
{
public:
	IEBesiegeTrigger();
	virtual ~IEBesiegeTrigger();
	virtual void Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param);
	static IEBesiegeTrigger * Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param);

public:
	virtual void Collision(IEPhysicNode * physicNode);
};

IE_END

#endif