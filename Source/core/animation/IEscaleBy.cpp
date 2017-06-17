#define __IE_DLL_EXPORTS__
#include "IEscaleBy.h"

IE_BEGIN

IEScaleBy::IEScaleBy(float &terminal, float duration)
{
	m_scaleBy = terminal;
	m_duration = duration;
	m_leftTime = duration;
}

IEScaleBy::~IEScaleBy()
{

}

void IEScaleBy::Initialization()
{

}

IEScaleBy * IEScaleBy::Create(float duration, float terminal)
{
	IEScaleBy * object = new IEScaleBy(terminal, duration);
	object->Initialization();
	return object;
}

//void IEScaleBy::SetCircleAndLoop(bool circle, bool loop)
//{
//	IEAnimation::SetCircleAndLoop(circle, loop);
//}

void IEScaleBy::CompletedAction(IENode * node)
{
	if (!m_hasCompletedAction)
	{
		m_hasCompletedAction = true;
		//m_startScale = node->GetScale();
		//m_terminalScale = node->GetScale() * m_scaleBy;
		//m_targetScale = node->GetScale() * m_scaleBy;
	}
}

void IEScaleBy::SetCircle()
{
	m_targetScale = m_startScale;
	m_leftTime = m_duration;
}

void IEScaleBy::SetLoop()
{
	if (m_circle)
	{
		if (m_targetScale == m_terminalScale)
		{
			m_targetScale = m_startScale;
		}
		else
		{
			m_targetScale = m_terminalScale;
		}
	}
	else
	{
		//m_animationNode->m_scale = m_startScale;
	}
	m_leftTime = m_duration;
}

bool IEScaleBy::Run(IENode * node)
{
	CompletedAction(node);

	//IEVector gap = m_targetScale - node->m_scale;
	IEVector gap = m_targetScale;
	IEVector segment = gap / m_leftTime * IETime::Share()->GetLastFrapPassingTime();
	//node->m_scale = node->m_scale + segment;
	m_leftTime = m_leftTime - IETime::Share()->GetLastFrapPassingTime();

	if (IsAnimationEnded())
	{
		//node->m_scale = m_targetScale;

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