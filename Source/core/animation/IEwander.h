/***********************************
* name     : IEwander.h
* creater  : cosc
* info     : wander to somewhere
* date     : 2016/12/9
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_WANDER__
#define __IE_WANDER__

#include "../IEnode.h"
#include "IEanimation.h"

IE_BEGIN

class IEWander :public IEAnimation
{
public:
	IEWander(float & durationRange, IEVector & spaceRange);
	virtual ~IEWander();
	virtual void Initialization();
	static IEWander * Create(float durationRange, IEVector & spaceRange);

public:
	virtual bool Run(IENode * node);
	virtual void CompletedAction(IENode * node);
	virtual void SetCircle();
	virtual void SetLoop();

	void RandomWander();

private:
	IEVector m_startPosition;
	IEVector m_spaceRange;
	float m_durationRange;
	IEVector m_targetPosition;
};

IE_END

#endif