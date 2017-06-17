/***********************************
* name     : IEanimation.h
* creater  : cosc
* info     : action base node
* date     : 2016/11/29
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ANIMATION__
#define __IE_ANIMATION__

#include "../IEobject.h"
#include "../container/IEstack.h"
#include "../../tools/IEtime.h"
#include "../../type/IEvector.h"

IE_BEGIN

class IENode;

#define INFINITE_TIMES 0

class IEAnimation:public IEObject
{
public:
	IEAnimation();
	~IEAnimation();
	static IEAnimation * Create();
	virtual void Initialization() = 0;

protected:
	virtual bool Run(IENode * node) = 0;
	virtual void CompletedAction(IENode * node) = 0;
	virtual void SetCircle() = 0;
	virtual void SetLoop() = 0;

	void ApplyNode(IENode * node);
	bool IsAnimationEnded();

public:
	virtual void SetCircleAndLoop(bool circle = false, bool loop = false);

protected:
	IENode * m_animationNode;

	float m_duration;
	float m_leftTime;
	float m_speed;

	bool m_circle;
	bool m_hasCompletedAction;
	bool m_loop;

	unsigned int m_times;
	unsigned int m_leftTimes;

	friend class IEAnimationNodeProtocol;
	friend class IESynchronizeAction;
};

IE_END

#endif