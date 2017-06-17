#define __IE_DLL_EXPORTS__
#include "IEanimationNodeProtocol.h"
#include "../IEnode.h"

IE_BEGIN

IEAnimationNodeProtocol::IEAnimationNodeProtocol()
{
	m_animationList = IEStack::Create();
	m_animationList->Retain();

	m_isAnimationRuning = true;
	m_curAnimation = NULL;
}

IEAnimationNodeProtocol::~IEAnimationNodeProtocol()
{
	AbandonCurAnimation();
	m_animationList->Release();
}

void IEAnimationNodeProtocol::RunAnimation()
{
	if (m_isAnimationRuning && m_curAnimation)
	{
		if (m_curAnimation->Run((IENode *)this))
		{
			GoNextAnimation();
		}
	}
}

void IEAnimationNodeProtocol::GoNextAnimation()
{
	AbandonCurAnimation();
	GetActionFromList();
}

void IEAnimationNodeProtocol::StartAnimation()
{
	m_isAnimationRuning = true;
}

void IEAnimationNodeProtocol::StopAnimation()
{
	m_isAnimationRuning = false;
}

void IEAnimationNodeProtocol::AbandonCurAnimation()
{
	if (m_curAnimation)
	{
		m_curAnimation->ReleaseDisreference();
		m_curAnimation = NULL;
	}
}

void IEAnimationNodeProtocol::AbandonRestAnimation()
{
	m_animationList->EmptyContainer();
}

void IEAnimationNodeProtocol::GetActionFromList()
{
	m_curAnimation = (IEAnimation *)m_animationList->PopFromBegining();
}

void IEAnimationNodeProtocol::ClearAnimations()
{
	AbandonCurAnimation();
	AbandonRestAnimation();
}

void IEAnimationNodeProtocol::AddAnimation(IEAnimation * animation)
{
	if (m_curAnimation == NULL)
	{
		m_curAnimation = animation;
		animation->ApplyNode((IENode *)this);
	}
	else
	{
		m_animationList->PushFromEnding(animation);
	}
}

void IEAnimationNodeProtocol::DeleteAnimation(IEAnimation * animation)
{
	if (m_curAnimation == animation)
	{
		AbandonCurAnimation();
	}
	else
	{
		//
	}
}

IE_END