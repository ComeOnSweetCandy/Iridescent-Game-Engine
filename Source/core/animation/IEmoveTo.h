/***********************************
* name     : IEmoveTo.h
* creater  : cosc
* info     : node move to somewhere
* date     : 2016/11/30
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MOVE_TO__
#define __IE_MOVE_TO__

#include "../IEnode.h"
#include "IEanimation.h"

IE_BEGIN

class IEMoveTo:public IEAnimation
{
public:
	IEMoveTo(IEVector &terminal, float duration);
	virtual ~IEMoveTo();
	virtual void Initialization();
	static IEMoveTo * Create(float duration, IEVector &terminal);

public:
	virtual bool Run(IENode * node);
	virtual void CompletedAction(IENode * node);
	virtual void SetCircle();
	virtual void SetLoop();

	//virtual void SetCircleAndLoop(bool circle = false, bool loop = false);

private:
	IEVector m_targetPosition;
	IEVector m_terminalPosition;
	IEVector m_startPosition;
};

IE_END

#endif