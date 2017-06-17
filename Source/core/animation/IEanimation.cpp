#define __IE_DLL_EXPORTS__
#include "IEanimation.h"
#include "../IEnode.h"

IE_BEGIN

IEAnimation::IEAnimation()
{
	m_duration = 1.0f;
	m_speed = 0.1f;
	m_circle = false;
	m_hasCompletedAction = false;
	m_loop = false;
	m_times = 0;
}

IEAnimation::~IEAnimation()
{

}

void IEAnimation::SetCircleAndLoop(bool circle, bool loop)
{
	m_circle = circle;
	m_loop = loop;
}

void IEAnimation::ApplyNode(IENode * node)
{
	m_animationNode = node;
}

bool IEAnimation::IsAnimationEnded()
{
	if (m_leftTime <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IE_END