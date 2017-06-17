#define __IE_DLL_EXPORTS__
#include "IEmoveTo.h"

IE_BEGIN

IEMoveTo::IEMoveTo(IEVector &terminal, float duration)
{
	m_terminalPosition = terminal;
	m_targetPosition = terminal;
	m_duration = duration;
	m_leftTime = duration;
}

IEMoveTo::~IEMoveTo()
{

}

void IEMoveTo::Initialization()
{

}

IEMoveTo * IEMoveTo::Create(float duration, IEVector &terminal)
{
	IEMoveTo * object = new IEMoveTo(terminal, duration);
	object->Initialization();
	return object;
}

//void IEMoveTo::SetCircleAndLoop(bool circle, bool loop)
//{
//	IEAnimation::SetCircleAndLoop(circle, loop);
//}

void IEMoveTo::CompletedAction(IENode * node)
{
	if (!m_hasCompletedAction)
	{
		m_hasCompletedAction = true;

		const float * translate = node->GetTranslate();
		m_startPosition = IEVector(translate[0], translate[1]);
	}
}

void IEMoveTo::SetCircle()
{
	m_targetPosition = m_startPosition;
	m_leftTime = m_duration;
}

void IEMoveTo::SetLoop()
{
	if (m_circle)
	{
		if (m_targetPosition == m_terminalPosition)
		{
			m_targetPosition = m_startPosition;
		}
		else
		{
			m_targetPosition = m_terminalPosition;
		}
	}
	else
	{
		m_animationNode->SetTranslate(m_startPosition.m_x, m_startPosition.m_y);
	}
	m_leftTime = m_duration;
}

bool IEMoveTo::Run(IENode * node)
{
	CompletedAction(node);

	const float * translate = node->GetTranslate();

	IEVector distance = m_targetPosition - IEVector(translate[0], translate[1]);
	IEVector segment = distance / m_leftTime * IETime::Share()->GetLastFrapPassingTime();

	node->SetTranslate(translate[0] + segment.m_x, translate[1] + segment.m_y);
	m_leftTime = m_leftTime - IETime::Share()->GetLastFrapPassingTime();

	if (IsAnimationEnded())
	{
		node->SetTranslate(m_targetPosition.m_x, m_targetPosition.m_y);

		if (m_loop)
		{
			SetLoop();
			return false;
		}
		else if (m_circle)
		{
			SetCircle();
			return false;
		}
		else 
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

IE_END